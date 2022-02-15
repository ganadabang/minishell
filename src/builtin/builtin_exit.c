/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:32:50 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/15 21:00:33 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "mush.h"

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

int	builtin_exit(t_state *state, int argc, char *argv[])
{
	(void)state;
	(void)argc;
	printf("exit\n");
	if (argc > 1)
	{
		if (!ft_str_alpha_check(argv[1]))
		{
			printf("mush: exit: %s: numberic argument required\n", argv[1]);
		}
		else if (argc > 2)
		{
			printf("mush: exit: too many arguments\n");
		}
	}
	exit(0);
}
