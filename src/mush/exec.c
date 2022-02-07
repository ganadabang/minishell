/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:31:28 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/07 14:25:00 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"
 
int mush_exec_builtin(t_state *state_ref)
{
	t_proc	*proc;
	t_array	*io_files_ref;
	int		(*fn)(t_state *, int, char *[]);
	int		fd_backup[2];


	proc = (t_proc *)state_ref->job.pipeline.data[0];
	io_files_ref = &proc->io_files;
	fd_backup[0] = dup(0);
	fd_backup[1] = dup(1);
	exec_io_redirect(proc);
	state_ref->last_status = fn(state_ref, proc->argv.len, (char **)proc->argv.data);
	dup2(fd_backup[0], 0);
	dup2(fd_backup[1], 1);
	close(fd_backup[0]);
	close(fd_backup[1]);
	return (state_ref->last_status);
}

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

void	mush_exec_simple_command(t_state *state, t_proc *proc)
{
	exec_pipe_connect(proc);
	exec_io_redirect(proc);
	proc->name = (char *)proc->argv.data[0];
	if (builtin_search(proc) == 0)
		exit(proc->fn_builtin(state, proc->argv.len, (char **)proc->argv.data));
	execve(proc->name, (char **)proc->argv.data, state->envp);
	exit(1);
}

int	mush_execute(t_state *state)
{
	t_proc		**procs;
	int			(*fn)(t_state *, int, char *[]);
	pid_t		pid;
	size_t		i;
	size_t		len;

	i = 0;
	len = state->job.pipeline.len;
	procs = (t_proc **)state->job.pipeline.data;
	procs[i]->name = (char *)procs[i]->argv.data[0];
	if (len == 1 && builtin_search(procs[i]))
		return (mush_exec_builtin(state));
	while (i < len - 1)
	{
		if (i + 1 < len - 1)
			exec_pipe_init(&procs[i]);
		pid = fork();
		if (pid < 0)
			ft_fatal("fork");
		if (pid == 0)
			mush_exec_simple_command(state, procs[i]);
		procs[i]->pid = pid;
		if (++i != len)
			close(procs[i]->stdout);
	}
	if (len != 1)
		close(procs[len - 1]->stdin);
	state->job.status = mush_job_status_update(&state->job.pipeline);
	return (state->last_status);
}