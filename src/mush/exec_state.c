/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:50:39 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/27 11:52:25 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "mush/exec.h"

int	exec_process_status_update(t_proc *procs[], size_t len)
{
	int		status;
	int		wpid;

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