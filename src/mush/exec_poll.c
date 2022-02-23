/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_poll.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:50:39 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/23 16:39:25 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "mush/parser.h"

static void	update_status(t_proc *proc, int status, int *is_signaled)
{
	if (WIFSIGNALED(status) == 1)
	{
		if (WTERMSIG(status) == SIGINT || WTERMSIG(status) == SIGQUIT)
			*is_signaled = 1;
		status = 128 + WTERMSIG(status);
	}
	else
		status = WEXITSTATUS(status);
	proc->status = status;
	return ;
}

int	mush_poll_status(t_array	*pipeline)
{
	t_proc	**procs;
	int		status;
	int		wpid;
	int		is_signaled;
	size_t	i;

	is_signaled = 0;
	procs = (t_proc **)pipeline->data;
	while (1)
	{
		wpid = wait(&status);
		if (wpid < 0)
			break ;
		i = 0;
		while (procs[i] != NULL && wpid != procs[i]->pid)
			++i;
		if (procs[i] != NULL)
			update_status(procs[i], status, &is_signaled);
	}
	while (wait(NULL) != -1)
		continue ;
	if (is_signaled == 1)
		write(1, "\n", 1);
	return (procs[pipeline->len - 1]->status);
}
