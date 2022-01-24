/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:31:28 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/24 23:46:36 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush/exec.h"

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
}
