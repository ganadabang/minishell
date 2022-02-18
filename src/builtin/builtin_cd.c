/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:30:14 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/19 13:44:02 by hyeonsok         ###   ########.fr       */
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
	char	*old_pwd;
	char	*path_value;
	int		i;

	i = 0;
	if (argc > 2)
	{
		ft_dputs(2, "mush: cd: to many arguments\n");
		return (1);
	}
	path_value = NULL;
	if (argc == 1)
	{
		path_value = mush_get_env(state, "HOME");
		if (path_value == NULL)
		{
			ft_dputs(2, "mush: cd: HOME not set\n");
			return (1);
		}
	}
	if (path_value == NULL)
		path_value = argv[1];
	old_pwd = getcwd(NULL, 0);
	if (chdir(path_value) < 0)
	{
		ft_dputs(2, "mush: cd: ");
		ft_dputendl(2, strerror(errno));
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL || old_pwd == NULL)
		mush_fatal("getcwd");
	mush_set_env(state, "OLDPWD", old_pwd);
	free(old_pwd);
	mush_set_env(state, "PWD", pwd);
	free(pwd);
	return (0);
}
