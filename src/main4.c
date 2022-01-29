/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:47:55 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/29 15:10:52 by hyeonsok         ###   ########.fr       */
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
	int		token_type;
}	t_token;

typedef struct s_proc {
	char	*name;
	char	**argv;
	t_array	io_files;
	pid_t	pid;
	int		status;
	int		(*fp_builtin)(char *[]);
	int		io_read;
	int		io_write;
}	t_proc;

typedef struct s_file {
	char	*name;
	int		io_type;
}	t_file;

typedef struct s_job {
	t_array	procs;
	int		status;
}	t_job;

typedef struct s_state {
	struct termios	term;
	t_job			*job;
	char			**envp;
	char			*pwd;
	char			*old_pwd;
	int				exit;
	int				last_status;
}	t_state;

typedef struct s_parser
{
	char	*input;
	t_array	tokens;
}	t_parser;

void	mush_sighandler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGWINCH)
		rl_on_new_line();
	return ;
}

void	mush_state_create(t_state *state, char **envrion)
{
	tcgetattr(STDOUT_FILENO, &state->term);
	state->job = NULL;
	state->envp = environ;//?
	state->exit = -1;
	state->last_status = 0;
}

void	mush_mode_interactive(struct termios *term)
{
	signal(SIGINT, mush_sighandler);
	term->c_lflag &= ~ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW ,term);
}

void	mush_mode_executive(struct termios *term)
{
	signal(SIGINT, SIG_IGN);
	term->c_lflag |= ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW ,term);
}

void	mush_signal(void)
{
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGWINCH, mush_sighandler);
	return ;
}

void	mush_term_restored(struct termios *term)
{
	term->c_lflag |= ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW ,term);
}


//TEST variables
t_file		files[] = { \
	{"outfile", IO_OUT}, \
	{"infile", IO_IN}, \
	{"outfile2", IO_APPEND} \
};

t_proc		procs[] = { \
	{"/bin/ls", (char *[]){"/bin/ls", NULL}, {0}, 0, 0, 0, 0, 1}, \
	{"/bin/cat", (char *[]){"/bin/cat", NULL}, {0}, 0, 0, 0, 0, 1}, \
	{"echo", (char *[]){"echo", "hello", NULL}, {0}, 0, 0, 0, 0, 1}, \
	{"/bin/ps", (char *[]){"/bin/ps", NULL}, {0}, 0, 0, 0, 0, 1}, \
	{"/usr/bin/grep", (char *[]){"/usr/bin/grep", "tty", NULL}, {0}, 0, 0, 0, 0, 1}, \
	{"/usr/bin/wc", (char *[]){"/usr/bin/wc", "-l", NULL}, {0}, 0, 0, 0, 0, 1} \
};
//__


int	mush_parser_tokenize(t_parser *parser)
{
	t_array		*tokens;
	t_buf		buffer;
	char		*input;
	char		ch;
	size_t		i;
	size_t		size;

	input = parser->input;
	tokens = &parser->tokens;
	memset(&buffer, 0, sizeof(t_buf));
	memset(tokens, 0, sizeof(t_array));
	i = strspn(input, " \t\n");
	while (input[i] != '\0')
	{
		ch = input[i];
		if (ch == '\n' || ch == '\t' || ch == ' ' || ch == '|' || ch == '<' \
			|| ch == '>' || ch == '"' || ch == '\'')
		{
			if (buffer.len > 0 && ch != '\'' && ch != '"')
			{
				hx_array_push(tokens, hx_buffer_withdraw(&buffer));
				i += strspn(&input[i], " \t\n");
			}
			else if (ch == '|' || ch == '<' || ch == '>')
			{
				size = 1 + (ch == input[i + 1] && (ch == '<' || ch == '>'));
				hx_buffer_putstr(&buffer, &input[i], size);
				hx_array_push(tokens, hx_buffer_withdraw(&buffer));
				i += size;
			}
			else if (input[i] == '"' || input[i] == '\'')
			{
				hx_buffer_putchar(&buffer, input[i++]);
				while (input[i] != '\0' && input[i] != ch)
					hx_buffer_putchar(&buffer, input[i++]);
				if (input[i] == '\0')
				{
					printf("mush: quoting unclosed\n");
					return (-1);
				}
				hx_buffer_putchar(&buffer, input[i++]);
			}
			continue ;
		}
		hx_buffer_putchar(&buffer, input[i++]);
	}
	hx_array_push(tokens, hx_buffer_withdraw(&buffer));
	hx_buffer_cleanup(&buffer);
	for (i = 0; i < tokens->len; ++i)
		printf("[%zu]: %s\n", i, (char *)tokens->data[i]);
	return (0);
}

// hx_array_push(&job->procs, &procs[3]);
// hx_array_push(&job->procs, &procs[4]);
// hx_array_push(&job->procs, &procs[5]);
// hx_array_push(&procs[2].io_files, &files[0]);
// hx_array_push(&procs[1].io_files, &files[2]);
// hx_array_push(&job->procs, &procs[1]);

int	mush_parse(t_state *state, char *input)
{
	t_parser	parser;

	if (input == NULL)
	{
		state->exit = 0;
		return (-1);
	}
	add_history(input);
	parser.input = input;
	mush_parser_tokenize(&parser);

	return (-1);
	// mush_job_create(&parser, state);
	// mush_parser_destroy(&parser);
	// if (mush_syntax_check(&state.job) == -1)
	// {
	// 	state->last_status = 258;
	// 	mush_job_destory(&state.job);
	// 	return (-1);
	// }
	// return (0);
}

void	mush_io_redirect(t_proc *proc)
{
	t_file	**io_files;
	int		fd;
	size_t	len;
	size_t	i;

	io_files = (t_file **)proc->io_files.data;
	len = proc->io_files.len;
	

	/*
		일단 open함. 그리고나서
		
		get_open_type;을 간결하게. heredoc만 조금 특수.
		
	*/

	i = -1;
	while (++i < len)
	{
		if (io_files[i]->io_type == IO_OUT)
		{
			close(proc->io_write);
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

int	builtin_search(const char *name, int (**f)(char *p[]));

int	mush_pipeline_status_update(t_job *job)
{
	t_proc **procs;
	int		status;
	int		wpid;
	size_t	len;
	size_t	i;

	procs = (t_proc **)job->procs.data;
	len = job->procs.len;
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
	return (procs[len - 1]->status);
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
	int			(*fn)(char *[]) = 0;

	job = state->job;
	len = job->procs.len;
	procs = (t_proc **)job->procs.data;
	proc = procs[0];

	//proc
	//builtin search는 command expansion에서 할 예정...
	// if (len == 1 && proc->fn)
	if (len == 1 && builtin_search(proc->name, &fn))
	{
		io_files = &proc->io_files;
		tmp[0] = dup(0);
		tmp[1] = dup(1);
		mush_io_redirect(proc);
		proc->status = fn(proc->argv);
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
				procs[i]->io_write = fd_pipe[1];
				procs[i + 1]->io_read = fd_pipe[0];
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
				if (proc->io_read != STDIN_FILENO)
				{
					dup2(proc->io_read, STDIN_FILENO);
					close(proc->io_read);
				}
				if (proc->io_write != STDOUT_FILENO)
				{
					dup2(proc->io_write, STDOUT_FILENO);
					close(proc->io_write);
				}
				mush_io_redirect(procs[i]);
				if (builtin_search(proc->name, &proc->fp_builtin))
					exit(proc->fp_builtin(proc->argv));
				execve(proc->name, proc->argv, environ);
			}
			proc->pid = pid;
			if (procs[i]->io_write != STDOUT_FILENO)
				close(procs[i]->io_write);
			++i;
		}
		close(procs[len - 1]->io_read);
		job->status = mush_pipeline_status_update(job);
		state->last_status = job->status;
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
	while (state.exit == -1)
	{
		mush_mode_interactive(&state.term);
		input = readline("mush+> ");
		if (mush_parse(&state, input) == -1)
		{
			continue ;
		}
		mush_mode_executive(&state.term);
		status = mush_execute(&state);
		if (status > 128)
			write(1, "\n", 1);
	}
	mush_term_restored(&state.term);
	write(1, "exit\n", 5);
	return (0);
}
