/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:50:39 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/15 20:51:05 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "mush/parser.h"

int	mush_job_status_update(t_array	*pipeline_ref)
{
	t_proc **procs;
	int		status;
	int		wpid;
	size_t	len;
	size_t	i;

	procs = (t_proc **)pipeline_ref->data;
	len = pipeline_ref->len;
	status = 0;
	while (1)
	{
		wpid = wait(&status);
		if (wpid < 0)
			break ;
		for (size_t i = 0; i < len; ++i)
		{
			if (wpid == procs[i]->pid)
			{	
				if (WIFSIGNALED(status) == 1)
				{
					procs[i]->status = 128 + WTERMSIG(status);
					write(1, "\n", 1);
					return (procs[len - 1]->status);
				}
				procs[i]->status = WEXITSTATUS(status);
			}
		}
	}
	return (procs[len - 1]->status);
}
