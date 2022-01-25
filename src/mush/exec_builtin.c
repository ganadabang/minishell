/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 20:54:27 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/25 23:58:32 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 경로에 대한 확인이고 이제 여기서 해야할 일은 ..
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
