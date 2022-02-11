/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 20:54:27 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/11 15:52:43 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush/parser.h"
#include "mush/builtin.h"
#include "libfthx.h"

static const struct s_builtin g_builtins[] = {
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
	cmp_len = ft_strlen(name) + 1;
	fn_ref = &proc->fn_builtin;
	i = 0;
	while (i < 7)
	{
		if (!ft_memcmp(builtins[i].name, name, cmp_len))
		{
			*fn_ref = g_builtins[i].builtin;
			return (1);
		}
		++i;
	}
	return (0);
}
