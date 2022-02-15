/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:42:14 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/16 00:54:14 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libfthx.h"
#include "mush/parser.h"

static const char *g_syntex_error_prefix = \
	"mush: syntax error unexpected token `";

static int	mush_syntax_error(t_parser *parser_ref)
{
	char	*unexpected;
	t_token	**tokens;
	size_t	len;
	size_t	i;

	unexpected = NULL;
	tokens = (t_token **)parser_ref->token_list.data;
	if (tokens[0]->type == TOKEN_PIPE)
		unexpected = "|";
	i = 0;
	while (tokens[++i - 1]->type != TOKEN_NEWLINE && unexpected == NULL)
	{
		if (tokens[i]->type == TOKEN_NEWLINE \
			&& tokens[i - 1]->type != TOKEN_WORD)
			unexpected = "newline";
		else if (tokens[i]->type == TOKEN_REDIR \
			&& tokens[i - 1]->type == TOKEN_REDIR)
			unexpected = tokens[i]->str;
		else if (tokens[i]->type == TOKEN_PIPE \
			&& tokens[i - 1]->type != TOKEN_WORD)
			unexpected = "|";
	}
	if (unexpected != NULL)
	{
		len = ft_strlen(unexpected);
		hx_buffer_cleanup(&parser_ref->buffer);
		hx_buffer_putstr(&parser_ref->buffer, g_syntex_error_prefix, 37);
		hx_buffer_putstr(&parser_ref->buffer, unexpected, len);
		hx_buffer_putstr(&parser_ref->buffer, "'\n", 3);
		return (-1);
	}
	return (0);
}

static int	mush_parser_with_input(t_state *state_ref, t_parser *parser_ref, \
	char *input)
{
	if (!input)
	{
		state_ref->exit = 0;
		return (-1);
	}
	if (!*input)
	{
		free(input);
		return (-1);
	}
	add_history(input);
	ft_memset(parser_ref, 0, sizeof(t_parser));
	parser_ref->input = input;
	return (0);
}

static void	mush_parser_destroy(t_parser *parser_ref)
{
	t_token	**tokens;
	size_t	i;

	tokens = (t_token **)parser_ref->token_list.data;
	i = parser_ref->token_list.len;
	while (i > 0)
	{
		free(tokens[--i]->str);
		free(tokens[i]);
	}
	hx_array_cleanup(&parser_ref->token_list);
	hx_buffer_cleanup(&parser_ref->buffer);
	free(parser_ref->input);
	return ;
}

static void	mush_parser_drop_input(t_parser *parser_ref, char **input_pref)
{
	parser_ref->input = NULL;
	free(*input_pref);
	*input_pref = NULL;
	return ;
}

int	mush_parser_readline(t_state *state_ref)
{
	t_parser	parser;
	char		*input;

	input = readline("mush+> ");
	if (mush_parser_with_input(state_ref, &parser, input) < 0)
		return (-1);
	if (mush_parser_tokenize(&parser) < 0 || mush_syntax_error(&parser) < 0)
	{
		ft_dputs(2, parser.buffer.data);
		state_ref->last_status = 258;
		mush_parser_destroy(&parser);
		return (-1);
	}
	mush_parser_drop_input(&parser, &input);
	mush_parser_init_pipeline(&state_ref->job.pipeline, &parser);
	hx_array_cleanup(&parser.token_list);
	return (0);
}
