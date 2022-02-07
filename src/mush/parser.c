/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:42:14 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/07 12:01:15 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

static int	mush_parser_with_input(t_parser *parser_ref, char *input)
{
	if (!input)
		return (-1);
	add_history(input);
	ft_memset(parser_ref, 0, sizeof(t_parser));
	parser_ref->input = input;
	return (0);
}

static void	mush_parser_destroy(t_parser *parser_ref)
{
	// TODO Be sure nodes of token_list are freed
	hx_array_cleanup(&parser_ref->token_list);
	hx_buffer_cleanup(&parser_ref->buffer);
	free(parser_ref->input);
}

static void	mush_parser_drop_input(t_parser *parser_ref, char **pref_input)
{
	parser_ref->input = NULL;
	free(*pref_input);
	*pref_input = NULL;
}

int	mush_parser_readline(t_state *ref_state)
{
	t_parser	parser;
	char		*input;

	input = readline("mush+> ");
	// NOTE ctrl+D
	if (mush_parser_with_input(&parser, input) < 0)
	{
		ref_state->exit = 0;
		return (-1);
	}
	// NOTE syntax error
	if (mush_parser_tokenize(&parser) < 0)
	{
		ref_state->last_status = 258;
		mush_parser_destroy(&parser);
		return (-1);
	}
	mush_parser_drop_input(&parser, &input);
	if (mush_parser_init_job(&ref_state->job.pipeline, &parser) < 0)
		return (-1);
	debug_pipeline(&ref_state->job.pipeline);
	return (0);
}