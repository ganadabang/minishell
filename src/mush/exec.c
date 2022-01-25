/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:31:28 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/26 01:20:27 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush/exec.h"
#include "mush/builtin.h"
#include "libft.h"
#include <sys/wait.h>
#include <sys/errno.h>

void	mush_exec(t_job *job)
{
	int			pde[2][2] = {{-1, -1}, {-1, -1}};
	pid_t		pid;
	int		(*f)(char *[]) = NULL;
	t_proc *proc = job->pipeline.data[0];

	//exec_builtin
	if (job->pipeline.len == 1 && builtin_search(proc->name, &f))
	{
		int	tmp[2];
		signal(SIGINT, SIG_DFL);
		tmp[0] = dup(0);
		tmp[1] = dup(1);
		io_redirect((t_file **)proc->io_redirect.data, proc->io_redirect.len);
		job->last_status = f(proc->argv);
		dup2(tmp[0], 0);
		dup2(tmp[1], 1);
		close(tmp[0]);
		close(tmp[1]);
		return ;
	}
	else
	{
		for (size_t i = 0; i < job->pipeline.len; ++i)
		{
			pipe(pde[0]);
			pid = fork();
			if (pid < 0)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			proc->pid = pid;
			t_proc *proc = job->pipeline.data[i];
			if (pid == 0)
			{
				signal(SIGINT, SIG_DFL);
				pipe_setup(pde, is_last_proc(i, job->pipeline.len));
				io_redirect((t_file **)proc->io_redirect.data, proc->io_redirect.len);
				//proc_expansioin
				//filename_expansion

				if(builtin_search(proc->name, &f))
					exit (f(proc->argv));
				else
					execve(proc->name, proc->argv, job->envp);
			}
			pipe_unset(pde);
		}
		close(pde[1][0]);
	}
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
					process->status = WIFSIGNALED(stat) * (128 + WTERMSIG(stat)) \
						+ WEXITSTATUS(stat);
			}
		}
	}
	job->last_status = ((t_proc *)job->pipeline.data[job->pipeline.len - 1])->status;
}
