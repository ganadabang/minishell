/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:50:39 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 13:28:15 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/errno.h>
#include <sys/wait.h>
#include "mush/parser.h"
#include <signal.h>

#include <stdio.h>

inline static int	is_interrupted(int status)
{
	return (WIFSIGNALED(status) == 1 \
		&& (WTERMSIG(status) == SIGINT || WTERMSIG(status) == SIGQUIT));
}

static void	update_status(t_proc *proc, int status)
{
	status = WEXITSTATUS(status);
	if (WIFSIGNALED(status) == 1)
		status = WTERMSIG(status);
	proc->status = status;
}

int	mush_poll_status(t_array	*pipeline)
{
	t_proc	**procs;
	int		status;
	int		wpid;
	size_t	len;
	size_t	i;

	procs = (t_proc **)pipeline->data;
	len = pipeline->len;
	while (1)
	{
		wpid = wait(&status);
		if (wpid < 0)
			break ;
		if (is_interrupted(status))
		{
			write(1, "\n", 1);
			return (128 + WTERMSIG(status));
		}
		i = 0;
		while (i < len)
		{
			if (wpid == procs[i]->pid)
				update_status(procs[i], status);
			++i;
		}
	}
	return (procs[len - 1]->status);
}
