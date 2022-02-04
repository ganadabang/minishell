/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:28:29 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/04 17:00:35 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush/builtin.h"
#include <stdio.h>

int	builtin_env(t_state *state, int argc, char *argv[])
{
	char	**env;
	char	*str;

	env = state->envp;
	if (ft_cnt_arg(argv) >= 2)
	{
		str = strerror(22);
		write(2, "env: ", 4);
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	return (0);
}
