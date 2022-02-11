/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 01:54:44 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/11 21:49:56 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libfthx.h"
#include "mush/parser.h"

static t_proc	*mush_create_simple_command(void)
{
	t_proc *proc;

	proc = ft_calloc(1, sizeof(t_proc));
	if (proc == NULL)
		mush_fatal("malloc");
	proc->stdout = 1;
	return (proc);
}

int	mush_parser_init_pipeline(t_array *pipeline, t_parser *parser)
{
	t_token	**tokens;
	t_proc	*process;
	t_file	*file;
	size_t	i;
	size_t	len;

	tokens = (t_token **)parser->token_list.data;
	len = parser->token_list.len;
	process = mush_create_simple_command();
	i = 0;
	while (i < len)
	{
		if (tokens[i]->type == TOKEN_REDIR)
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
		else
			hx_array_push(&process->argv, tokens[i]->str);
		free(tokens[i]);
		++i;
	}
	hx_array_push(pipeline, process);
	return (0);
}
