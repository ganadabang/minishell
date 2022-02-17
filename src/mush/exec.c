/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:31:28 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/17 13:23:23 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/errno.h>
#include "libfthx.h"
#include "mush/exec.h"
#include "mush/builtin.h"
#include "mush/signal.h"

void	exec_pipe_init(t_proc **procs)
{
	int fd_pipe[2];

	pipe(fd_pipe);
	procs[0]->stdout = fd_pipe[1];
	procs[1]->stdin = fd_pipe[0];
}

void	exec_pipe_connect(t_proc *proc)
{
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
}

void	exec_check_cmd(char *name, char *argv[])
{
	if (!name)
	{
		ft_dputs(2, argv[0]);
		ft_dputendl(2, ": command not found");
		exit(127);
	}
	if (access(name, F_OK) < 0 || access(name, X_OK) < 0)
	{
		perror(argv[0]);
		exit(errno);
	}
	ft_putendl(name);
	return ;
}

void	mush_exec_simple_command(t_state *state_ref, t_proc *proc)
{
	mush_signal_restored();
	exec_pipe_connect(proc);
	exec_io_redirect(state_ref, &proc->io_files);
	exec_expn_argv(state_ref, &proc->argv);
	proc->argv.data[0] = exec_expn_cmd(state_ref, proc->argv.data[0]);
	proc->name = proc->argv.data[0];
	exec_check_cmd(proc->name, (char **)proc->argv.data);
	if (builtin_search(proc) == 1)
		exit(proc->fn_builtin(state_ref, proc->argv.len, (char **)proc->argv.data));
	execve(proc->name, (char **)proc->argv.data, state_ref->envp);
}

void	mush_execute(t_state *state)
{
	t_proc		**procs;
	int			(*fn)(t_state *, int, char *[]);
	pid_t		pid;
	size_t		i;
	size_t		len;

	i = 0;
	len = state->job.pipeline.len;
	procs = (t_proc **)state->job.pipeline.data;
	procs[i]->name = (char *)(procs[i]->argv.data[0]);
	if (len == 1 && builtin_search(procs[i]))
		state->job.status = mush_exec_builtin(state);
	else
	{
		while (i < len)
		{
			if (i + 1 < len)
				exec_pipe_init(&procs[i]);
			pid = fork();
			if (pid < 0)
				mush_fatal("fork");
			if (pid == 0)
				mush_exec_simple_command(state, procs[i]);
			procs[i]->pid = pid;
			if (i + 1 != len)
				close(procs[i]->stdout);
			++i;
		}
		if (len != 1)
			close(procs[len - 1]->stdin);
		state->job.status = mush_job_status_update(&state->job.pipeline);
	}
	free(state->last_status);
	state->last_status = ft_itoa(state->job.status);
	if (state->last_status == NULL)
		mush_fatal("malloc");
	return ;
}
