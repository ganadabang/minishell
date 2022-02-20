/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:31:28 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/20 21:44:47 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/errno.h>
#include <string.h>
#include "libfthx.h"
#include "mush/exec.h"
#include "mush/builtin.h"
#include "mush/signal.h"

static void	exec_proc_pipe_init(t_proc **procs, int pipe_fd[2])
{
	if (pipe(pipe_fd) < 0)
		mush_fatal("pipe");
	procs[0]->stdout = pipe_fd[1];
	procs[1]->stdin = pipe_fd[0];
	return ;
}

static void	exec_proc_pipe_redirection(t_proc *proc, int toclose)
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
	close(toclose);
	return ;
}

void	exec_run_simple_command(t_state *state_ref, t_proc *proc, int toclose)
{
	size_t	len;
	pid_t	pid;

	len = state_ref->job.pipeline.len;
	exec_expn_argv(state_ref, &proc->argv);
	proc->name = (char *)proc->argv.data[0];
	if (builtin_search(proc) == 1 && len == 1)
		mush_exec_builtin(state_ref);
	else
	{
		pid = fork();
		if (pid < 0)
			mush_fatal("fork");
		if (pid == 0)
		{
			exec_proc_pipe_redirection(proc, toclose);
			mush_signal_restored();
			exec_proc_io_redirect(state_ref, &proc->io_files);
			if (proc->fn_builtin != NULL)
				exit(proc->fn_builtin(state_ref, proc->argv.len, \
					(char **)proc->argv.data));
			proc->name = exec_expn_cmd(state_ref, proc->argv.data[0]);
			if (proc->name == NULL)
			{
				ft_dputs(2, "mush: ");
				ft_dputs(2, (char *)proc->argv.data[0]);
				ft_dputs(2, ": command not found\n");
				exit(127);
			}
			execve(proc->name, (char **)proc->argv.data, \
			(char **)state_ref->envlist.data);
			ft_dputs(2, "mush: ");
			ft_dputs(2, proc->name);
			ft_dputs(2, ": ");
			ft_dputendl(2, strerror(errno));
			if (errno == ENOEXEC || errno == EACCES)
				exit(126);
			exit(127);
		}
		proc->pid = pid;
	}
	return ;
}


void	mush_execute(t_state *state)
{
	t_proc		**procs;
	int			pipe_fd[2];
	size_t		len;
	size_t		i;

	procs = (t_proc **)state->job.pipeline.data;
	pipe_fd[0] = -1;
	len = state->job.pipeline.len;
	i = 0;
	while (i < len - 1)
	{
		exec_proc_pipe_init(&procs[i], pipe_fd);
		exec_run_simple_command(state, procs[i], pipe_fd[0]);
		if (procs[i]->stdin != STDIN_FILENO)
			close(procs[i]->stdin);
		close(procs[i]->stdout);
		++i;
	}
	exec_run_simple_command(state, procs[i], pipe_fd[0]);
	if (pipe_fd[0] != -1)
		close(procs[i]->stdin);
	state->job.status = mush_job_status_update(&state->job.pipeline);
	if (state->job.status != 0)
	{
		free(state->last_status);
		state->last_status = ft_itoa(state->job.status);
		if (state->last_status == NULL)
			mush_fatal("malloc");
	}
	return ;
}