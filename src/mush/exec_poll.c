/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_poll.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:50:39 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/23 16:07:11 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "mush/parser.h"

static int	update_status(t_proc *proc, int status)
{
	if (WIFSIGNALED(status) == 1)
	{
		if (WTERMSIG(status) == SIGINT || WTERMSIG(status) == SIGQUIT)
			write(1, "\n", 1);
		status = 128 + WTERMSIG(status);
	}
	else
		status = WEXITSTATUS(status);
	proc->status = status;
	return (1);
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
			break ;
		i = 0;
		while (procs[i] != NULL && wpid != procs[i]->pid)
			++i;
		if (procs[i] != NULL && !update_status(procs[i], status))
			break ;
	}
	while (wait(NULL) != -1)
		continue ;
	return (procs[pipeline->len - 1]->status);
}
