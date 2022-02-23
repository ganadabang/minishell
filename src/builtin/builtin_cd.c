/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:30:14 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/23 16:28:01 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/errno.h>
#include "libft.h"
#include "mush/builtin.h"

static void	update_env_pwd(t_state *state, char *old_pwd)
{
	char	*pwd;

	mush_set_env(state, "OLDPWD", old_pwd);
	free(old_pwd);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		mush_fatal("getcwd");
	mush_set_env(state, "PWD", pwd);
	free(pwd);
	return ;
}

static int	get_home_path(t_state *state, char **path_value_ref)
{
	char	*path_value;

	path_value = mush_get_env(state, "HOME");
	if (path_value == NULL)
	{
		mush_error("cd", "HOME not set");
		return (-1);
	}
	*path_value_ref = path_value;
	return (0);
}

int	builtin_cd(t_state *state, int argc, char *argv[])
{
	char	*old_pwd;
	char	*path_value;

	if (argc > 2)
	{
		mush_error("cd", "to many arguments");
		return (1);
	}
	if (argc == 1 && get_home_path(state, &path_value) < 0)
		return (1);
	else if (argc == 2)
		path_value = argv[1];
	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
		mush_fatal("getcwd");
	if (chdir(path_value) < 0)
	{
		free(old_pwd);
		mush_error(path_value, strerror(errno));
		return (1);
	}
	update_env_pwd(state, old_pwd);
	return (0);
}
