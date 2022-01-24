/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:28:29 by gpaeng            #+#    #+#             */
/*   Updated: 2021/11/19 20:11:10 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char *args[])
{
	char	**env;

	env = jop.envp;
	if (ft_cnt_arg(args) >= 2)
	{
		printf("en: '%s': No such file or directory\n", args[1]);
		return ;
	}
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
