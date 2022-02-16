/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:42:14 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/17 04:44:12 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libfthx.h"
#include "mush/parser.h"

static int	mush_parser_with_input(t_state *state_ref, t_parser *parser_ref, \
	char *input)
{
	if (input == NULL || input[ft_strspn(input, " \t\n")] == '\0')
	{
		if (input == NULL)
			state_ref->exit = 0;
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
	while (i-- > 0)
	{
		free(tokens[i]->str);
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
		free(state_ref->last_status);
		state_ref->last_status = ft_itoa(258);
		mush_parser_destroy(&parser);
		return (-1);
	}
	mush_parser_drop_input(&parser, &input);
	mush_parser_init_pipeline(&state_ref->job.pipeline, &parser);
	hx_array_cleanup(&parser.token_list);
	return (0);
}
