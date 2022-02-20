/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 01:54:44 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/20 18:17:56 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libfthx.h"
#include "mush/parser.h"

static t_proc	*mush_create_simple_command(void)
{
	t_proc	*proc;

	proc = (t_proc *)malloc(sizeof(t_proc));
	if (proc == NULL)
		mush_fatal("malloc");
	ft_memset(proc, 0, sizeof(t_proc));
	ft_memset(&proc->io_files, 0, sizeof(t_array));
	ft_memset(&proc->argv, 0, sizeof(t_array));
	proc->stdout = 1;
	return (proc);
}

static void	proc_push_file(t_proc *process, t_token **tokens, size_t *idx)
{
	t_file	*file;
	size_t	i;

	i = *idx;
	file = parser_create_io_file(&tokens[i]->str, tokens[i + 1]->str);
	free(tokens[i]);
	free(tokens[++i]);
	hx_array_push(&process->io_files, file);
	*idx = i;
	return ;
}

static void	proc_push_word(t_proc *process, t_token **tokens, size_t i)
{
	hx_array_push(&process->argv, tokens[i]->str);
	free(tokens[i]);
	return ;
}

static void	pipeline_push_proc(t_array *pipeline, t_proc **process_ref, \
	t_token **tokens, size_t i)
{
	free(tokens[i]->str);
	free(tokens[i]);
	hx_array_push(pipeline, *process_ref);
	*process_ref = NULL;
	*process_ref = mush_create_simple_command();
	return ;
}

void	mush_parser_init_pipeline(t_array *pipeline, t_parser *parser)
{
	t_token	**tokens;
	t_proc	*process;
	size_t	i;

	tokens = (t_token **)parser->token_list.data;
	process = mush_create_simple_command();
	i = 0;
	while (tokens[i]->type != TOKEN_NEWLINE)
	{
		if (tokens[i]->type == TOKEN_REDIR)
			proc_push_file(process, tokens, &i);
		else if (tokens[i]->type == TOKEN_WORD)
			proc_push_word(process, tokens, i);
		else if (tokens[i]->type == TOKEN_PIPE)
			pipeline_push_proc(pipeline, &process, tokens, i);
		++i;
	}
	free(tokens[i]->str);
	free(tokens[i]);
	hx_array_push(pipeline, process);
}
