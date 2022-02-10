/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 20:54:27 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/10 15:19:13 by gpaeng           ###   ########.fr       */
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

int	builtin_search(const char *name, int (**fn)(t_state *, int, char *[]))
{
	size_t	i;

	i = 0;
	while (i < 7)
	{
		if (!strcmp(builtins[i].name, name))
		{
			*fn = builtins[i].builtin;
			return (1);
		}
		++i;
	}
	return (0);
}