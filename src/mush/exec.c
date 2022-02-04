/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:31:28 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/04 19:53:26 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

int	mush_execute(t_state *state)
{
	pid_t		pid;
	t_job		*job = NULL;
	t_proc		**procs;
	t_proc		*proc = NULL;
	t_array		*io_files;
	int			status;
	int			tmp[2];
	
	size_t		len = 0;
	int			(*fn)(t_state *, int, char *[]) = 0;

	job = &state->job;
	len = job->pipeline.len;
	procs = (t_proc **)job->pipeline.data;
	proc = procs[0];
	proc->name = (char *)proc->argv.data[0];
	if (len == 1 && builtin_search(proc->name, &fn))
	{
		io_files = &proc->io_files;
		tmp[0] = dup(0);
		tmp[1] = dup(1);
		mush_io_redirect(proc);
		proc->status = fn(state, proc->argv.len, (char **)proc->argv.data);
		dup2(tmp[0], 0);
		dup2(tmp[1], 1);
		close(tmp[0]);
		close(tmp[1]);
		job->status = proc->status;
		state->last_status = job->status;
		return (state->last_status);
	}
	{
		pid_t	pid;
		size_t	i;

		i = 0;
		while (i < len)
		{
			if (i < len - 1)
			{
				int fd_pipe[2];

				pipe(fd_pipe);
				procs[i]->stdout = fd_pipe[1];
				procs[i + 1]->stdin = fd_pipe[0];
			}
			pid = fork();
			if (pid < 0)
			{
				
				perror("fork");
				exit(EXIT_FAILURE);
			}
			if (pid == 0)
			{
				proc = procs[i];
				proc->name = (char *)proc->argv.data[0];
				if (proc->stdin != STDIN_FILENO)
				{
					dup2(proc->stdin, STDIN_FILENO);
					close(proc->stdin);
				}
				if (proc->stdout != STDOUT_FILENO)
				{
					dup2(proc->stdout, STDOUT_FILENO);
					close(proc->stdout);
				}
				mush_io_redirect(procs[i]);
				if (builtin_search(proc->name, &proc->fp_builtin))
					exit(proc->fp_builtin(state, proc->argv.len, (char **)proc->argv.data));
				execve(proc->name, (char **)proc->argv.data, state->envp);
				exit(1);
			}
			proc->pid = pid;
			if (procs[i]->stdout != STDOUT_FILENO)
				close(procs[i]->stdout);
			++i;
		}
		if (procs[len - 1]->stdin != STDIN_FILENO)
			close(procs[len - 1]->stdin);
		state->last_status = mush_job_status_update(job);
		return (state->last_status);
	}
}