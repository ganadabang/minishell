/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:34:22 by gpaeng            #+#    #+#             */
/*   Updated: 2021/11/01 17:56:59 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_str_length(char *str)
{
	int cnt;

	cnt = 0;
	while (*str)
	{
		cnt++;
		str++;
	}
	return (cnt);
}

int ft_echo_option(char *str)
{
	int str_length;

	str_length = ft_str_length(str);
	if (str[0] == '-' && str[str_length - 1] == 'n')
		return (1);
	return (0);
}

void ft_echo_print(char *args[])
{
	while (*args)
	{
		printf("%s", *args);
		if (*(args + 1) != NULL)
			printf(" ");
		args++;
	}
}

void ft_echo(char *args[])
{
	
	int option;
	
	option = 0;
	args++; //echo 다음 문자열

	if (ft_echo_option(*args)) {
		args++;
		option = 1;
	}
	ft_echo_print(args);
	if (!option)
		printf("\n");
}
