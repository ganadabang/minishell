/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:42:14 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/04 19:45:28 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"


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