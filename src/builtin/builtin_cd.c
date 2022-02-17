/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:30:14 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/17 15:20:43 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/errno.h>
#include "libft.h"
#include "mush/builtin.h"

int	builtin_cd(t_state *state, int argc, char *argv[])
{
	char	*pwd;
	char	*path_value;
	int		i;

	i = 0;
	if (argc > 2)
	{
		ft_dputendl(2, "mush: cd: to many arguments");
		return (1);
	}
	path_value = NULL;
	if (argc == 1)
	{
		path_value = mush_getenv(state, "HOME");
		if (path_value == NULL)
		{
			ft_dputendl(2, "mush: cd: HOME not set");
			return (1);
		}
	}
	if (path_value == NULL)
		path_value = argv[1];
	if (chdir(path_value) < 0)
	{
		ft_dputs(2, "mush: cd: ");
		ft_dputendl(2, strerror(errno));
		return (1);
	}
	// mush_setenv(state, "OLDPWD", mush_getenv(state, "PWD"));
	// pwd = getcwd(NULL, 0);
	// if (pwd == NULL)
	// 	mush_fatal("getcwd");
	// mush_setenv(state, "PWD", pwd);
	// free(pwd);
	return (0);
}
