/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:32:39 by gpaeng            #+#    #+#             */
/*   Updated: 2022/01/24 21:28:03 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(char *args[])
{
	char	buf[4096];
	char	*pwd;

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
