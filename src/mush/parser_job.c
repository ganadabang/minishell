/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 01:54:44 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/05 12:36:29 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

t_proc	*mush_create_simple_command(void)
{
	t_proc *proc;

	proc = calloc(1, sizeof(t_proc));
	proc->stdout = 1;
	return (proc);
}

int	mush_parser_init_job(t_array *pipeline, t_parser *parser)
{
	char	*unexpected;
	t_token	**tokens;
	t_proc	*process;
	t_file	*file;
	size_t	i;

	if (mush_syntax_error(parser, &unexpected) != 0)
	{
		printf("mush: syntax error near unexpected token `%s'\n", unexpected);
		return (-1);
	}
	tokens = (t_token **)parser->token_list.data;
	process = mush_create_simple_command();
	i = 0;
	while ((tokens[i])->type != TOKEN_NEWLINE)
	{
		if (tokens[i]->type == TOKEN_WORD)
			hx_array_push(&process->argv, tokens[i]->str);
		else if (tokens[i]->type == TOKEN_REDIR)
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
		++i;
	}
	hx_array_push(pipeline, process);
}