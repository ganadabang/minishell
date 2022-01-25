/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:28:29 by gpaeng            #+#    #+#             */
/*   Updated: 2022/01/25 23:34:23 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush/builtin.h"
#include <stdio.h>

int	builtin_env(char *args[])
{
	char	**env;
	char	*str;

	env = jop.envp;
	if (ft_cnt_arg(args) >= 2)
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
