/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 20:54:27 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 11:24:54 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "mush/builtin.h"
#include "mush/exec.h"
#include "libfthx.h"

static const struct s_builtin	g_builtins[] = {\
	{"cd", builtin_cd}, \
	{"echo", builtin_echo}, \
	{"env", builtin_env}, \
	{"exit", builtin_exit}, \
	{"export", builtin_export}, \
	{"pwd", builtin_pwd}, \
	{"unset", builtin_unset} \
};

int	builtin_search(t_proc *proc)
{
	char	*name;
	int		(**fn_ref)(t_state *, int, char *[]);
	size_t	cmp_len;
	size_t	i;

	if (proc->argv.len == 0)
		return (0);
	name = (char *)proc->argv.data[0];
	cmp_len = ft_strlen(name) + 1;
	fn_ref = &proc->fn_builtin;
	i = 0;
	while (i < 7)
	{
		if (!ft_memcmp(g_builtins[i].name, name, cmp_len))
		{
			*fn_ref = g_builtins[i].builtin;
			proc->name = name;
			return (1);
		}
		++i;
	}
	return (0);
}

void	mush_exec_builtin(t_state *state_ref)
{
	t_proc	*proc;
	t_array	*io_files_ref;
	int		fd_backup[2];

	proc = (t_proc *)state_ref->job.pipeline.data[0];
	io_files_ref = &proc->io_files;
	fd_backup[0] = dup(0);
	fd_backup[1] = dup(1);
	if (exec_proc_iofile_redirect(state_ref, io_files_ref) < 0)
	{
		state_ref->job.status = 1;
		return ;
	}
	state_ref->job.status = proc->fn_builtin(state_ref, proc->argv.len, \
		(char **)proc->argv.data);
	dup2(fd_backup[0], 0);
	dup2(fd_backup[1], 1);
	close(fd_backup[0]);
	close(fd_backup[1]);
	return ;
}
