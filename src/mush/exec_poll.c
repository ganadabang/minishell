/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_poll.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:50:39 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 17:00:21 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "mush/parser.h"

inline static int	is_interrupted(int status)
{
	return (WIFSIGNALED(status) == 1 \
		&& (WTERMSIG(status) == SIGINT || WTERMSIG(status) == SIGQUIT));
}

static void	update_status(t_proc *proc, int status)
{
	if (WIFSIGNALED(status) == 1)
		status = WTERMSIG(status);
	else
		status = WEXITSTATUS(status);
	proc->status = status;
}

int	mush_poll_status(t_array	*pipeline)
{
	t_proc	**procs;
	int		status;
	int		wpid;
	size_t	i;

	procs = (t_proc **)pipeline->data;
	while (1)
	{
		wpid = wait(&status);
		if (wpid < 0)
			return (procs[pipeline->len - 1]->status);
		if (is_interrupted(status) == 1)
			break ;
		i = 0;
		while (procs[i] != NULL)
		{
			if (wpid == procs[i]->pid)
				break ;
			++i;
		}
		update_status(procs[i], status);
	}
	write(1, "\n", 1);
	return (128 + WTERMSIG(status));
}
