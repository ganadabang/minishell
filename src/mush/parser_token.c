/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 01:54:46 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/11 21:27:48 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libfthx.h"
#include "mush/parser.h"

static void	parser_skip_blanks(t_parser *parser_ref)
{
	char	*input;
	size_t	pos;

	input = parser_ref->input;
	pos = parser_ref->pos;
	parser_ref->pos += ft_strspn(&input[pos], " \t\n");
	return ;
}

static void	parser_peekchar(t_parser *parser_ref, char *ch_ref)
{
	*ch_ref = parser_ref->input[parser_ref->pos];
	return ;
}

static int	parser_get_next_tokenstr(t_parser *parser_ref, char **tokstr_ref)
{
	char	ch;

	parser_skip_blanks(parser_ref);
	parser_peekchar(parser_ref, &ch);
	while (ch != '\0')
	{
		if (parser_ref->buffer.len > 0 && ft_strchr(" \t\n<|>", ch))
			break ;
		if (ft_strchr("<|>", ch) != NULL)
		{
			*tokstr_ref = parser_buffer_withdraw_operator(parser_ref);
			return (0);
		}
		if (ft_strchr("\"'", ch) != NULL)
		{
			if (parser_buffer_write_quoted(parser_ref, ch) < 0)
			{
				hx_buffer_cleanup(&parser_ref->buffer);
				if (!hx_buffer_putstr(&parser_ref->buffer, \
					"mush: syntax error unclosed quotation mark\n" ,45))
					mush_fatal("malloc");
				return (-1);
			}
		}
		else
			parser_buffer_write_char(parser_ref, ch);
		parser_peekchar(parser_ref, &ch);
	}
	hx_buffer_putchar(&parser_ref->buffer, '\0');
	*tokstr_ref = parser_buffer_withdraw_word(parser_ref);
	return (0);
}

static t_token	*parser_create_token(char *token_string)
{
	t_token	*token;
	int		type;
	char	ch;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		mush_fatal("malloc");
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

	while (1)
	{
		if (parser_get_next_tokenstr(parser_ref, &token_string) < 0)
			return (-1);
		if (token_string == NULL)
			break ;
		token = parser_create_token(token_string);
		hx_array_push(&parser_ref->token_list, token);
		if (token->type == TOKEN_NEWLINE)
			break ;
	}
	hx_buffer_cleanup(&parser_ref->buffer);
	return (0);
}
