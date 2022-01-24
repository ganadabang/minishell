/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:32:50 by gpaeng            #+#    #+#             */
/*   Updated: 2022/01/24 23:40:19 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush/builtin.h"

int	ft_str_alpha_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	builtin_exit(char *args[])
{
	printf("exit\n");
	if (ft_cnt_arg(args) > 1)
	{
		if (!ft_str_alpha_check(args[1]))
		{
			printf("minishell: exit: %s: numberic argument required\n", args[1]);
		}
		else if (ft_cnt_arg(args) > 2)
		{
			printf(">minishell: exit: too many arguments\n");
		}
	}
	exit(0);
}
