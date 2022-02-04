/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:42:14 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/05 02:10:32 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

static int	mush_parser_with_input(t_parser *ref_parser, char *input)
{
	if (!input)
		return (-1);
	add_history(input);
	ft_memset(ref_parser, 0, sizeof(t_parser));
	ref_parser->input = input;
	return (0);
}

static void	mush_parser_destroy(t_parser *ref_parser)
{
	// TODO Be sure nodes of token_list are freed
	hx_array_cleanup(&ref_parser->token_list);
	hx_buffer_cleanup(&ref_parser->buffer);
	free(ref_parser->input);
}

static void	mush_parser_drop_input(t_parser *ref_parser, char **pref_input)
{
	ref_parser->input = NULL;
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