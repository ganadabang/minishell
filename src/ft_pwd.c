/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:32:39 by gpaeng            #+#    #+#             */
/*   Updated: 2022/01/06 12:56:04 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void ft_pwd(char *args[]) 
{
	char buf[4096];
	char *pwd;
	(void)args;
	if (getcwd(buf, 4096) == NULL)
	{
		pwd = ft_get_env("PWD");
		printf("%s\n", pwd);
		free(pwd);
	}
	else
		printf("%s\n", buf);
}
