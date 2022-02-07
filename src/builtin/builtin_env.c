/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:28:29 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/05 17:14:34 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"
#include <stdio.h>

int	builtin_env(t_state *state, int argc, char *argv[])
{
	char	**env;
	char	*str;

	env = state->envp;
	if (argc > 1)
	{
		str = strerror(22);
		write(2, "env: ", 4);
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	else
	{
		while (*env)
		{
			printf("%s\n", *env);
			env++;
		}
	}
	return (0);
}
