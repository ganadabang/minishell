/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 01:54:46 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/05 12:37:42 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

// TODO: strspn -> ft_strspn
static void	parser_skip_blanks(t_parser *ref_parser)
{
	char	*input;
	size_t	pos;

	input = ref_parser->input;
	pos = ref_parser->pos;
	ref_parser->pos += strspn(&input[pos], " \t\n");
	return ;
}

static char	parser_peekchar(t_parser *ref_parser, char *ref_ch)
{
	*ref_ch = ref_parser->input[ref_parser->pos];
	return (*ref_ch);
}



// TODO: strchr -> ft_strchr
static char	*parser_get_next_tokenstr(t_parser *ref_parser)
{
	char	ch;

	parser_skip_blanks(ref_parser);
	parser_peekchar(ref_parser, &ch);
	while (ch != '\0')
	{
		if (ref_parser->buffer.len > 0 && strchr(" \t\n<|>", ch))
			break ;
		if (strchr("<|>", ch) != NULL)
			return (parser_buffer_withdraw_operator(ref_parser));
		if (strchr("\"'", ch) != NULL)
		{
			if (parser_buffer_write_quoted(ref_parser, ch) < 0)
				return (NULL);
		}
		else
			parser_buffer_write_char(ref_parser, ch);
		parser_peekchar(ref_parser, &ch);
	}
	return (parser_buffer_withdraw_word(ref_parser));
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

int	mush_parser_tokenize(t_parser *ref_parser)
{
	t_token		*token;
	char		*token_string;
	char		*unexpected;

	token_string = parser_get_next_tokenstr(ref_parser);
	while (token_string != NULL && !ref_parser->syntax_error)
	{
		token = parser_create_token(token_string);
		hx_array_push(&ref_parser->token_list, token);
		if (token->type == TOKEN_NEWLINE)
			break ;
		token_string = parser_get_next_tokenstr(ref_parser);
	}
	hx_buffer_cleanup(&ref_parser->buffer);
	if (ref_parser->syntax_error != 0)
	{
		printf("mush: syntax error unclosed quoting\n");
		return (-1);
	}
	return (0);
}
