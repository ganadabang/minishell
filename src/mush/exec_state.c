/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:50:39 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/04 19:43:16 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

int	mush_job_status_update(t_job *job)
{
	t_proc **procs;
	int		status;
	int		wpid;
	size_t	len;
	size_t	i;

	procs = (t_proc **)job->pipeline.data;
	len = job->pipeline.len;
	while (1)
	{
		wpid = wait(&status);
		if (errno == ECHILD)
			break ;
		for (size_t i = 0; i < len; ++i)
		{
			if (wpid == procs[i]->pid)
			{
				status = WIFSIGNALED(status);
				status *= (128 + WTERMSIG(status));
				status += WEXITSTATUS(status);
				procs[i]->status = status;
			}
		}
	}
	job->status = procs[len - 1]->status;
	return (job->status);
}
