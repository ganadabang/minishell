/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 14:37:28 by gpaeng            #+#    #+#             */
/*   Updated: 2021/08/19 15:51:59 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// 출력을 하는 함수입니다.
// -n : 마지막에 따라오는 개행문자(new line)문자를 출력하지 않습니다.
// echo를 파악하고 들어온 것이라고 생각합니다.
// 출력에서 빈칸이 아무리 많아도 *argv 사이 빈칸은 하나이다

int ft_echo_option(char *str)
{
	int idx;

	idx = 0;
	if (str[idx] == '-' && str[idx + 1] == 'n')
		return (1);
	return (0);
}

void ft_echo_print(char *argv[])
{
	while (*argv)
	{
		printf("%s", *argv);
		if (*(argv + 1) != NULL)
			printf(" ");
		argv++;
	}
}

void ft_echo(char *argv[])
{
	
	int option;
	
	option = 0;
	argv++; //echo 다음 문자열

	if (ft_echo_option(*argv)) {
		option = 1;
	}
	ft_echo_print(argv);
	if (!option)
		printf("\n");
}
