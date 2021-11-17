/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:32:50 by gpaeng            #+#    #+#             */
/*   Updated: 2021/11/17 15:43:34 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_exit(char *args[])
{
	printf("exit\n");
	if (ft_cnt_arg(args) > 1)
	{
		if (ft_strisdigit(args[1]))
		{
			printf("minishell: exit: %s: numberic argument required", args[1]);
		}
		else if (ft_cnt_arg(args) > 2)
		{
			printf(">minishell: exit: too many arguments");
		}
	}
	exit(0);
}
