/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 22:04:01 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/16 23:32:20 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mush/parser.h"

static const char	*g_syntex_error_prefix = \
	"mush: syntax error unexpected token `";

static void	parser_put_syntax_error(t_buf *buffer_ref, const char *unexpected)
{
	size_t	len;

	len = ft_strlen(unexpected);
	hx_buffer_cleanup(buffer_ref);
	hx_buffer_putstr(buffer_ref, g_syntex_error_prefix, 37);
	hx_buffer_putstr(buffer_ref, unexpected, len);
	hx_buffer_putstr(buffer_ref, "'\n", 3);
	return ;
}

static int	parser_check_unexpected(enum e_mush_token cur_type, \
	enum e_mush_token prev_type)
{
	if (cur_type == TOKEN_NEWLINE && prev_type != TOKEN_WORD
		|| cur_type == TOKEN_REDIR && prev_type == TOKEN_REDIR
		|| cur_type == TOKEN_PIPE && prev_type != TOKEN_WORD)
		return (-1);
	return (0);
}

int	mush_syntax_error(t_parser *parser_ref)
{
	char	*unexpected;
	t_token	**tokens;
	size_t	len;
	size_t	i;

	unexpected = NULL;
	tokens = (t_token **)parser_ref->token_list.data;
	if (tokens[0]->type == TOKEN_PIPE)
		unexpected = "|";
	len = parser_ref->token_list.len;
	i = 0;
	while (unexpected == NULL && ++i < len)
	{
		if (parser_check_unexpected(tokens[i]->type, tokens[i - 1]->type) < 0)
			unexpected = tokens[i]->str;
	}
	if (unexpected != NULL)
	{
		if (*unexpected == '\0')
			unexpected = "newline";
		parser_put_syntax_error(&parser_ref->buffer, unexpected);
		return (-1);
	}
	return (0);
}
