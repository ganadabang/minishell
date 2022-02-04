/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:34:22 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/04 20:33:18 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"
#include <stdio.h>

int	ft_strlength(char *str)
{
	int	cnt;
	int idx;

	cnt = 0;
	idx = 0;
	while (str[idx])
	{
		cnt++;
		idx++;
	}
	return (cnt);
}

int	ft_check_option(int str_length, char *str)
{
	int	idx;

	idx = 1;
	while (idx < str_length)
	{
		if (str[idx] != 'n')
			return (0);
		idx++;
	}
	return (1);
}

int	ft_echo_option(char *str)
{	int str_length;

	str_length = ft_strlength(str);
	if (ft_check_option(str_length, str))
		return (1);
	return (0);
}

void	ft_echo_print(char *argv[])
{
	while (*argv)
	{
		printf(">>>%s", *argv);
		if (*(argv + 1) != NULL)
			printf(" ");
		argv++;
	}
}

int	builtin_echo(t_state *state, int argc, char *argv[])
{
	int	option;

	option = 0;
	argv++;
	if (*argv && ft_echo_option(*argv))
	{
		argv++;
		option = 1;
	}
	ft_echo_print(argv);
	if (!option)
		printf("\n");
	return (0);
}
