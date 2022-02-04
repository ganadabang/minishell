/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:47:55 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/04 16:00:46 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <string.h>

#include "libftx.h"
#include "mush/mode.h"

extern char	**environ;

enum	e_iotype {
	IO_IN,
	IO_OUT,
	IO_APPEND,
	IO_HERE
};

typedef struct	s_word {
	char	*str;
	int		word_type;
}	t_word;

typedef struct	s_token {
	char	*str;
	int		type;
}	t_token;

typedef struct s_proc {
	char	*name;
	t_array	argv;
	t_array	io_files;
	pid_t	pid;
	int		status;
	int		(*fp_builtin)(char *[]);
	int		stdin;
	int		stdout;
}	t_proc;

typedef struct s_file {
	char	*name;
	int		io_type;
	int		oflag;
}	t_file;

typedef struct s_job {
	t_array	pipeline;
	int		status;
}	t_job;

typedef struct s_state {
	struct termios	term;
	t_job			job;
	char			**envp;
	char			*pwd;
	char			*old_pwd;
	int				exit;
	int				last_status;
}	t_state;

typedef struct s_parser
{
	t_array	token_list;
	char	*input;
	int		syntax_error;
	size_t	pos;
}	t_parser;

struct s_quoted_word {
	int		word_type;
	char	*str;
};

void	mush_state_create(t_state *state, char **envp)
{
	tcgetattr(STDOUT_FILENO, &state->term);
	state->envp = envp;
	state->exit = -1;
	state->last_status = 0;
}
int	is_operator(char ch)
{
	return (ch == '>' || ch == '<' || ch == '|');
}

int	is_quoting(char ch)
{
	return (ch == '\'' || ch == '"');
}

int	is_blank(char ch)
{
	return (ch == '\n' || ch == ' ' || ch == '\t');
}

int	is_meta(char ch)
{
	return (is_blank(ch) || is_quoting(ch) || is_operator(ch));
}

size_t	get_operator_size(char *input)
{
	if (!is_operator(input[0]))
		return (0);
	if (input[0] == input[1] && (input[0] == '<' || input[0] == '>'))
		return (2);
	return (1);
}

int	parser_buffer_write_quoted(t_parser *parser, t_buf *buffer, char quoting)
{
	char	*cur;
	char	*brk;
	size_t	len;

	cur = &parser->input[parser->pos];
	brk = strchr(&cur[1], quoting);
	if (!brk)
	{
		parser->syntax_error = 1;
		return (-1);
	}
	len = brk - cur + 1;
	hx_buffer_putstr(buffer, cur, len);
	parser->pos += len;
	return (0);
}

void	parser_buffer_write_operator(t_parser *parser, t_buf *buffer)
{
	char	*cur;
	size_t	len;
	int		ret;

	cur = &parser->input[parser->pos];
	len = get_operator_size(cur);
	hx_buffer_putstr(buffer, cur, len);
	parser->pos += len;
	return ;
}

void	parser_peekchar(t_parser *parser, char *ch)
{
	*ch = parser->input[parser->pos];
	return ;
}

char	*parser_get_next_token(t_parser *parser, t_buf *buffer)
{
	char	ch;

	parser->pos += strspn(&parser->input[parser->pos], " \t\n");
	parser_peekchar(parser, &ch);
	while (ch != '\0')
	{
		if ((is_blank(ch) || is_operator(ch)) && buffer->len > 0)
			break ;
		if (is_operator(ch))
		{
			parser_buffer_write_operator(parser, buffer);
			return (hx_buffer_withdraw(buffer));
		}
		if (is_quoting(ch))
		{
			if (parser_buffer_write_quoted(parser, buffer, ch) == -1)
				return (NULL);
			parser_peekchar(parser, &ch);
			continue ;
		}
		hx_buffer_putchar(buffer, ch);
		parser->pos += 1;
		parser_peekchar(parser, &ch);
	}
	return (hx_buffer_withdraw(buffer));
}

enum e_mush_token {
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR,
	TOKEN_NEWLINE
};

t_token	*parser_create_token(char *token_string)
{
	t_token	*token;
	char	ch;
	int		type;

	token = (t_token *)malloc(sizeof(t_token));
	token->str = token_string;
	ch = *token_string;
	{
		if (ch == '|')
			type = TOKEN_PIPE;
		else if (ch == '<' || ch == '>')
			type = TOKEN_REDIR;
		else if (ch == '\0')
			type = TOKEN_NEWLINE;
		else
			type = TOKEN_WORD;
	}
	token->type = type;
	return (token);
}

int	mush_syntax_error(t_parser *parser, char **unexpected)
{
	t_token	**tokens;
	size_t	i;

	*unexpected = NULL;
	tokens = (t_token **)parser->token_list.data;
	if (tokens[0]->type == TOKEN_PIPE)
		*unexpected = "|";
	i = 0;
	while (tokens[++i - 1]->type != TOKEN_NEWLINE && *unexpected == NULL)
	{
		if (tokens[i]->type == TOKEN_NEWLINE \
			&& tokens[i - 1]->type != TOKEN_WORD)
			*unexpected = "newline";
		else if (tokens[i]->type == TOKEN_REDIR \
			&& tokens[i - 1]->type == TOKEN_REDIR)
			*unexpected = tokens[i]->str;
		else if (tokens[i]->type == TOKEN_PIPE \
			&& tokens[i - 1]->type != TOKEN_WORD)
			*unexpected = "|";
	}
	if (*unexpected != NULL)
		parser->syntax_error = 1;
	return (parser->syntax_error);
}

int	mush_parser_tokenize(t_parser *parser)
{
	t_buf		buffer;
	t_token		*token;
	char		*token_string;
	char		*unexpected;

	memset(&buffer, 0, sizeof(t_buf));
	token_string = parser_get_next_token(parser, &buffer);
	while (token_string != NULL && !parser->syntax_error)
	{
		token = parser_create_token(token_string);
		hx_array_push(&parser->token_list, token);
		if (token->type == TOKEN_NEWLINE)
			break ;
		token_string = parser_get_next_token(parser, &buffer);
	}
	hx_buffer_cleanup(&buffer);
	if (parser->syntax_error != 0)
		printf("mush: syntax error unclosed quoting\n");
	else if (mush_syntax_error(parser, &unexpected) != 0)
		printf("mush: syntax error near unexpected token `%s'\n", unexpected);
	return (parser->syntax_error);
}

int	get_io_type(char *str)
{
	if (strcmp("<<", str) == 0)
		return (IO_HERE);
	if (strcmp(">>", str) == 0)
		return (IO_APPEND);
	if (strcmp("<", str) == 0)
		return (IO_IN);
	if (strcmp(">", str) == 0)
		return (IO_OUT);
	return (-1);
}

int	get_oflag(int io_type)
{
	if (io_type == IO_HERE || io_type == IO_IN)
		return (O_RDONLY);
	if (io_type == IO_OUT)
		return (O_CREAT | O_TRUNC | O_WRONLY);
	if (io_type == IO_APPEND)
		return (O_CREAT | O_APPEND | O_WRONLY);
	return (-1);
}

char	*remove_quoting(char *str)
{
	t_buf	buffer;
	char	*ret;

	ft_memset(&buffer, 0, sizeof(buffer));
	while (*str)
	{
		if (*str != '\'' && *str != '"')
			hx_buffer_putchar(&buffer, *str);
		++str;
	}
	ret = hx_buffer_withdraw(&buffer);
	hx_buffer_cleanup(&buffer);
	return (ret);
}

t_file	*parser_create_io_file(char *redir, char *str)
{
	t_file	*file;
	char	*filename;
	char	*here_end;

	file = (t_file *)calloc(1, sizeof(t_file));
	file->io_type = get_io_type(redir);
	file->oflag = get_oflag(file->io_type);
	file->name = str;
	if (file->io_type == IO_HERE)
	{
		int		fd;
		int		tmp;
		char	*input;

		here_end = remove_quoting(str);
		file->name = "./.here_tmp";
		fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		while (1)
		{
			input = readline(">");
			if (strcmp(here_end, input) == 0)
				break ;
			ft_dputendl(fd, input);
		}
		close(fd);
	}
	return (file);
}

t_proc	*mush_create_simple_command(void)
{
	t_proc *proc;

	proc = calloc(1, sizeof(t_proc));
	proc->stdout = 1;
	return (proc);
}

void	debug_pipeline(t_array *pipeline)
{
	size_t		i;
	size_t		j;
	char		**argv;
	size_t		maxlen;
	t_array		*io_files;
	size_t		len;

	
	printf("\npipeline->len: %zu\n", pipeline->len);
	i = 0;
	len = pipeline->len;
	while (len-- > 0)
	{
		printf("\nprocess:[%zu]\n", i);
		
		argv = (char **)((t_proc *)pipeline->data[i])->argv.data;
		maxlen = ((t_proc *)pipeline->data[i])->argv.len;
		j = 0;
		while (j < maxlen)
		{
			printf("argv[%zu]: %s\n", j, (char *)argv[j]);
			++j;
		}
		io_files = &((t_proc *)pipeline->data[i])->io_files;
		maxlen = io_files->len;
		j = 0;
		while (j < maxlen)
		{
			printf("io_type: %d\tfilename: %s\n", ((t_file *)io_files->data[j])->io_type, ((t_file *)io_files->data[j])->name);
			++j;
		}
		++i;
	}
	return ;
}

void	mush_job_create(t_array *pipeline, t_parser *parser)
{
	t_token	**tokens;
	t_proc	*process;
	t_file	*file;
	size_t	i;

	ft_memset(pipeline, 0, sizeof(t_array));
	tokens = (t_token **)parser->token_list.data;
	process = mush_create_simple_command();
	i = 0;
	while ((tokens[i])->type != TOKEN_NEWLINE)
	{
		if (tokens[i]->type == TOKEN_WORD)
			hx_array_push(&process->argv, tokens[i]->str);
		else if (tokens[i]->type == TOKEN_REDIR)
		{
			file = parser_create_io_file(tokens[i]->str, tokens[i + 1]->str);
			hx_array_push(&process->io_files, file);
			++i;
		}
		else if (tokens[i]->type == TOKEN_PIPE)
		{
			hx_array_push(pipeline, process);
			process = mush_create_simple_command();
		}
		++i;
	}
	hx_array_push(pipeline, process);
	debug_pipeline(pipeline);
}

int	mush_parse(t_state *state, char *input)
{
	t_parser	parser;
	char		*unexpected;
	int			status;

	if (!*input)
		return (-1);
	add_history(input);
	memset(&parser, 0, sizeof(t_parser));
	parser.input = input;
	if (mush_parser_tokenize(&parser) != 0)
	{
		state->last_status = 258;
		//mush_parser_destroy()
		return (-1);
	}
	free(input);
	mush_job_create(&state->job.pipeline, &parser);
	return (0);
}

void	mush_io_redirect(t_proc *proc)
{
	t_file	**io_files;
	int		fd;
	size_t	len;
	size_t	i;

	io_files = (t_file **)proc->io_files.data;
	len = proc->io_files.len;
	i = -1;
	while (++i < len)
	{
		if (io_files[i]->io_type == IO_OUT)
		{
			close(proc->stdout);
			fd = open(io_files[i]->name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (fd < 0 || dup2(fd, 1) < 0)
				break ;
			close(fd);
		}
		else if (io_files[i]->io_type == IO_IN)
		{
			fd = open(io_files[i]->name, O_RDONLY, 0644);
			if (fd < 0 || dup2(fd, 0) < 0)
				break ;
			close(fd);
		}
		else if (io_files[i]->io_type == IO_APPEND)
		{
			fd = open(io_files[i]->name, O_CREAT | O_WRONLY | O_APPEND , 0644);
			if (fd < 0 || dup2(fd, 1) < 0)
				break ;
			close(fd);
		}
		else if (io_files[i]->io_type == IO_HERE)
		{
			fd = open("./.heredoc.tmp", O_RDONLY, 0644);
			if (fd < 0 || dup2(fd, 0))
				break ;
			close(fd);
			unlink("./.herdoc.tmp");
		}
	}
	return ;
}

int	builtin_search(const char *name, int (**fn)(int, char *av[], char *ep[]));

int	mush_job_status_update(t_job *job)
{
	t_proc **procs;
	int		status;
	int		wpid;
	size_t	len;
	size_t	i;

	procs = (t_proc **)job->pipeline.data;
	len = job->pipeline.len;
	while (1)
	{
		wpid = wait(&status);
		if (errno == ECHILD)
			break ;
		for (size_t i = 0; i < len; ++i)
		{
			if (wpid == procs[i]->pid)
			{
				status = WIFSIGNALED(status);
				status *= (128 + WTERMSIG(status));
				status += WEXITSTATUS(status);
				procs[i]->status = status;
			}
		}
	}
	job->status = procs[len - 1]->status;
	return (job->status);
}

int	mush_execute(t_state *state)
{
	pid_t		pid;
	t_job		*job = NULL;
	t_proc		**procs;
	t_proc		*proc = NULL;
	t_array		*io_files;
	int			status;
	int			tmp[2];
	
	size_t		len = 0;
	int			(*fn)(int, char *[], char *[]) = 0;

	job = &state->job;
	len = job->pipeline.len;
	procs = (t_proc **)job->pipeline.data;
	proc = procs[0];
	proc->name = (char *)proc->argv.data[0];
	if (len == 1 && builtin_search(proc->name, &fn))
	{
		io_files = &proc->io_files;
		tmp[0] = dup(0);
		tmp[1] = dup(1);
		mush_io_redirect(proc);
		proc->status = fn(proc->argv.len, (char **)proc->argv.data, state->envp);
		dup2(tmp[0], 0);
		dup2(tmp[1], 1);
		close(tmp[0]);
		close(tmp[1]);
		job->status = proc->status;
		state->last_status = job->status;
		return (state->last_status);
	}
	{
		pid_t	pid;
		size_t	i;

		i = 0;
		while (i < len)
		{
			if (i < len - 1)
			{
				int fd_pipe[2];

				pipe(fd_pipe);
				procs[i]->stdout = fd_pipe[1];
				procs[i + 1]->stdin = fd_pipe[0];
			}
			pid = fork();
			if (pid < 0)
			{
				
				perror("fork");
				exit(EXIT_FAILURE);
			}
			if (pid == 0)
			{
				proc = procs[i];
				proc->name = (char *)proc->argv.data[0];
				if (proc->stdin != STDIN_FILENO)
				{
					dup2(proc->stdin, STDIN_FILENO);
					close(proc->stdin);
				}
				if (proc->stdout != STDOUT_FILENO)
				{
					dup2(proc->stdout, STDOUT_FILENO);
					close(proc->stdout);
				}
				mush_io_redirect(procs[i]);
				if (builtin_search(proc->name, &proc->fp_builtin))
					exit(proc->fp_builtin((char **)proc->argv.data));
				execve(proc->name, (char **)proc->argv.data, environ);
			}
			proc->pid = pid;
			if (procs[i]->stdout != STDOUT_FILENO)
				close(procs[i]->stdout);
			++i;
		}
		close(procs[len - 1]->stdin);
		state->last_status = mush_job_status_update(job);
		return (state->last_status);
	}
}

int	main(int argc, char *argv[])
{
	t_state	state;
	int		status;
	char	*input;

	mush_state_create(&state, environ);
	mush_signal();
	while (1)
	{
		mush_mode_interactive(&state.term);
		input = readline("mush+> ");
		if (!input)
			break ;
		if (mush_parse(&state, input) == -1)
			continue ;
		mush_mode_executive(&state.term);
		status = mush_execute(&state);
		if (status > 128)
			write(1, "\n", 1);
	}
	mush_term_restored(&state.term);
	write(1, "exit\n", 5);
	return (0);
}
