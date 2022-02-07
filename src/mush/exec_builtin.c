/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 20:54:27 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/07 13:37:53 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

static const struct s_builtin builtins[] = {
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
	size_t	i;
	
	name = proc->name;
	fn_ref = &proc->fn_builtin;
	i = 0;
	while (i < 7)
	{
		// TODO: strcmp -> ft_strcmp
		if (!strcmp(builtins[i].name, name))
		{
			*fn_ref = builtins[i].builtin;
			return (1);
		}
		++i;
	}
	return (0);
}