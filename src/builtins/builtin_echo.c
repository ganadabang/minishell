/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:34:22 by gpaeng            #+#    #+#             */
/*   Updated: 2022/01/24 21:27:44 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_str_length(char *str)
{
	int	cnt;

	cnt = 0;
	while (*str)
	{
		cnt++;
		str++;
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
{
	int	str_length;

	str_length = ft_str_length(str);
	if (ft_check_option(str_length, str))
		return (1);
	return (0);
}

void	ft_echo_print(char *args[])
{
	while (*args)
	{
		printf("%s", *args);
		if (*(args + 1) != NULL)
			printf(" ");
		args++;
	}
}

void	builtin_echo(char *args[])
{
	int	option;

	option = 0;
	args++;
	if (ft_echo_option(*args))
	{
		args++;
		option = 1;
	}
	ft_echo_print(args);
	if (!option)
		printf("\n");
}
