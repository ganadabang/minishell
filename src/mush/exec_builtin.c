/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 20:54:27 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/17 02:59:35 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "mush/builtin.h"
#include "mush/exec.h"
#include "libfthx.h"

static const struct s_builtin	g_builtins[] = { \
	{"cd", builtin_cd},
	{"echo", builtin_echo},
	{"env", builtin_env},
	{"exit", builtin_exit},
	{"export", builtin_export},
	{"pwd", builtin_pwd},
	{"unset", builtin_unset}
};

int	builtin_search(t_proc *proc)
{
	char	*name;
	int		(**fn_ref)(t_state *, int, char *[]);
	size_t	cmp_len;
	size_t	i;

	name = proc->name;
	if (name == NULL)
		return (0);
	cmp_len = ft_strlen(name) + 1;
	fn_ref = &proc->fn_builtin;
	i = 0;
	while (i < 7)
	{
		if (!ft_memcmp(g_builtins[i].name, name, cmp_len))
		{
			*fn_ref = g_builtins[i].builtin;
			return (1);
		}
		++i;
	}
	return (0);
}

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
	exec_io_redirect(state_ref, io_files_ref);
	exec_expn_argv(state_ref, &proc->argv);
	state_ref->last_status = proc->fn_builtin(state_ref, proc->argv.len, \
		(char **)proc->argv.data);
	dup2(fd_backup[0], 0);
	dup2(fd_backup[1], 1);
	close(fd_backup[0]);
	close(fd_backup[1]);
	return (state_ref->last_status);
}
