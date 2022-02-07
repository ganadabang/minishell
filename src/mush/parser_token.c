/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 01:54:46 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/07 12:01:31 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

// TODO: strspn -> ft_strspn
static void	parser_skip_blanks(t_parser *parser_ref)
{
	char	*input;
	size_t	pos;

	input = parser_ref->input;
	pos = parser_ref->pos;
	parser_ref->pos += strspn(&input[pos], " \t\n");
	return ;
}

static char	parser_peekchar(t_parser *parser_ref, char *ch_ref)
{
	*ch_ref = parser_ref->input[parser_ref->pos];
	return (*ch_ref);
}



// TODO: strchr -> ft_strchr
static char	*parser_get_next_tokenstr(t_parser *parser_ref)
{
	char	ch;

	parser_skip_blanks(parser_ref);
	parser_peekchar(parser_ref, &ch);
	while (ch != '\0')
	{
		if (parser_ref->buffer.len > 0 && strchr(" \t\n<|>", ch))
			break ;
		if (strchr("<|>", ch) != NULL)
			return (parser_buffer_withdraw_operator(parser_ref));
		if (strchr("\"'", ch) != NULL)
		{
			if (parser_buffer_write_quoted(parser_ref, ch) < 0)
				return (NULL);
		}
		else
			parser_buffer_write_char(parser_ref, ch);
		parser_peekchar(parser_ref, &ch);
	}
	return (parser_buffer_withdraw_word(parser_ref));
}

t_token	*parser_create_token(char *token_string)
{
	t_token	*token;
	char	ch;
	int		type;

	token = (t_token *)malloc(sizeof(t_token));
	token->str = token_string;
	ch = *token_string;
	if (ch == '|')
		type = TOKEN_PIPE;
	else if (ch == '<' || ch == '>')
		type = TOKEN_REDIR;
	else if (ch == '\0')
		type = TOKEN_NEWLINE;
	else
		type = TOKEN_WORD;
	token->type = type;
	return (token);
}

int	mush_parser_tokenize(t_parser *parser_ref)
{
	t_token		*token;
	char		*token_string;
	char		*unexpected;

	token_string = parser_get_next_tokenstr(parser_ref);
	while (token_string != NULL && !parser_ref->syntax_error)
	{
		token = parser_create_token(token_string);
		hx_array_push(&parser_ref->token_list, token);
		if (token->type == TOKEN_NEWLINE)
			break ;
		token_string = parser_get_next_tokenstr(parser_ref);
	}
	hx_buffer_cleanup(&parser_ref->buffer);
	if (parser_ref->syntax_error != 0)
	{
		printf("mush: syntax error unclosed quoting\n");
		return (-1);
	}
	return (0);
}
