/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:34:22 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/15 21:02:12 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "mush/parser.h"

static int	ft_check_option(int str_length, char *str)
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

static int	ft_echo_option(char *str)
{	
	size_t	str_length;

	str_length = ft_strlen(str);
	if (ft_check_option(str_length, str))
		return (1);
	return (0);
}

void	ft_echo_print(char *argv[])
{
	size_t	i;

	i = 0;
	while (1)
	{
		if (argv[i] == NULL)
			return ;
		printf("%s", argv[i]);
		if (argv != NULL)
			printf(" ");
		argv++;
	}
	return ;
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
