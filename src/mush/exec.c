/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:31:28 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/25 17:51:10 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush/exec.h"
#include <sys/wait.h>
#include <sys/errno.h>

void	mush_exec(t_job *job)
{
	int			pde[2][2] = {{-1, -1}, {-1, -1}};
	pid_t		pid;

	for (size_t i = 0; i < job->pipeline.len; ++i)
	{
		pipe(pde[0]);
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		t_proc *proc = job->pipeline.data[i];
		proc->pid = pid;
		if (pid == 0)
		{
			pipe_setup(pde, is_last_proc(i, job->pipeline.len));
			io_redirect((t_file **)proc->io_redirect.data, proc->io_redirect.len);
			//proc_expansioin
			//filename_expansion
			execve(proc->name, proc->argv, job->envp);
			puts("Error");
		}
		pipe_unset(pde);
	}
	close(pde[1][0]);
	//update_status; It's going to be separated.
	int	stat;
	int	ret;
	t_proc	*process;
	while (1)
	{
		ret = wait(&stat);
		if (errno == ECHILD)
			break ;
		for (size_t i = 0; i < job->pipeline.len; ++i)
		{
			process = (t_proc *)job->pipeline.data[i];
			if (ret == process->pid)
			{
				if (process->iscompleted == 0)
				{
					// process->iscompleted = 1;
					process->status = stat >> 8;
					//debug
					dprintf(2, "ret:%d status:%d\n", ret, stat >> 8);
				}
			}
		}
	}
	job->last_status = ((t_proc *)job->pipeline.data[job->pipeline.len - 1])->status;
}
