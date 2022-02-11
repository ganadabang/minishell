/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 01:54:41 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/11 16:01:18 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfthx.h"
#include "mush/parser.h"

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