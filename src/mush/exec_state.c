/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:50:39 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/07 12:48:27 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

int	mush_job_status_update(t_array	*pipeline_ref)
{
	t_proc **procs;
	int		status;
	int		wpid;
	size_t	len;
	size_t	i;

	procs = (t_proc **)pipeline_ref->data;
	len = pipeline_ref->len;
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
	return (procs[len - 1]->status);
}
