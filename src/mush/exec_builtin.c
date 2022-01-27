/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 20:54:27 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/27 12:30:10 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush/exec.h"
#include "mush/builtin.h"

static const struct s_builtin builtins[] = {
	{"cd", builtin_cd},
	{"echo", builtin_echo},
	{"env", builtin_env},
	{"exit", builtin_exit},
	{"exit", builtin_export},
	{"pwd", builtin_pwd},
	{"unset", builtin_unset}
};

int	builtin_search(const char *name, int (**f)(char *p[]))
{
	size_t	i;

	i = -1;
	while (++i < 7)
	{
		if (!strcmp(builtins[i].name, name ))
		{
			*f = builtins[i].builtin;
			return (1);
		}
	}
	return (0);
}

int	exec_builtin_on_parent(t_array *io_files, char **argv)
{
	int	status;
	int	tmp[2];
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	tmp[0] = dup(0);
	tmp[1] = dup(1);
	io_redirect((t_file **)io_files->data, io_files->len);
	status = f(argv);
	dup2(tmp[0], 0);
	dup2(tmp[1], 1);
	close(tmp[0]);
	close(tmp[1]);
	return (f(argv));
}