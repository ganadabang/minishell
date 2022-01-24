/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:32:39 by gpaeng            #+#    #+#             */
/*   Updated: 2022/01/24 23:41:07 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush/builtin.h"

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
