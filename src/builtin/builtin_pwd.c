/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:32:39 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/04 20:49:27 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mush.h"

int	builtin_pwd(t_state *state, int argc, char *argv[])
{
	char	buf[4096];
	char	*pwd;

	(void)argv;
	if (getcwd(buf, 4096) == NULL)
	{
		pwd = state->pwd;
		printf("%s\n", pwd);
		free(pwd);
	}
	else
		printf("%s\n", buf);
	return (0);
}
