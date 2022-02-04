/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 20:54:27 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/04 15:55:30 by gpaeng           ###   ########.fr       */
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

int	builtin_search(const char *name, int (**f)(int, char *av[], char *ep[]))
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

// int	mush_execute_builtin(t_array *io_files, char **argv)
// {
// 	int	status;
// 	int	tmp[2];

// 	signal(SIGQUIT, SIG_DFL);
// 	signal(SIGINT, SIG_DFL);
// 	tmp[0] = dup(0);
// 	tmp[1] = dup(1);
// 	io_redirect((t_file **)io_files->data, io_files->len);
// 	status = f(argv);
// 	dup2(tmp[0], 0);
// 	dup2(tmp[1], 1);
// 	close(tmp[0]);
// 	close(tmp[1]);
// }