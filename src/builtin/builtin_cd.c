/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:30:14 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/17 03:13:26 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libfthx.h"
#include "mush/builtin.h"

//To be removed
#include <string.h>

char	**ft_update_env(t_state *state, char *path_n, char *path_v)
{
	int		i;
	int		j;
	char	*path;
	char	*path_name;
	char	**env;

	i = 0;
	mush_env_realloc(state);
	while (env[i])
	{
		j = ft_chrspn(env[i], '=');
		if (ft_strncmp(env[i], path_n, j - 1) == 0)
		{
			path_name = strndup(env[i], j + 1);
			env[i] = ft_strjoin(path_name, path_v);
			free(path_name);
			free(path);
		}
		i++;
	}
	env[i] = 0;
	return (env);
}

char	*get_pwd(t_state *state)
{
	char	buffer[4096];
	char	*pwd;

	if (getcwd(buffer, 4096) == 0)
	{
		pwd = state->pwd;
		return (pwd);
	}
	pwd = ft_strdup(buffer);
	return (pwd);
}

int	ft_do_chdir(t_state *state, char *path_v, char *oldpwd, char **argv)
{
	struct stat	file_buffer;
	char		*pwd;
	char		**env;
	int			file_status;

	printf("");
	if (chdir(path_v) == -1)
	{
		chdir(oldpwd);
		file_status = stat(*argv, &file_buffer);
		if (file_status == -1 && ft_strncmp(argv[0], "-", 1))
			printf("mush: cd: %s No such file or directory\n", argv[0]);
		else if (file_status == 0)
			printf("mush: cd: %s Not a directory\n", argv[0]);
		return (1);
	}
	pwd = get_pwd(state);
	state->envp = ft_update_env(state, "OLDPWD", oldpwd);
	state->envp = ft_update_env(state, "PWD", pwd);
	return (0);
}

int	ft_check_args_cd(t_state *state, int argc, char *argv[])
{
	char	*path_value;
	char	*pwd;

	if (argc > 2)
	{
		printf("mush: cd: too many arguments\n");
		return (0);
	}
	else if (argc == 2)
	{
		pwd = state->pwd;
		if (ft_strncmp(argv[0], "-", 1) == 0)
		{
			path_value = getenv("OLDPWD");
			ft_do_chdir(state, path_value, pwd, argv);
			printf("%s\n", pwd);
		}
	}
	return (1);
}

int	builtin_cd(t_state *state, int argc, char *argv[])
{
	char	**splitted_path;
	char	*pwd;
	char	*path_value;
	int		i;

	argv++;
	i = 0;
	if (!ft_check_args_cd(state, argc, argv))
		return (1);
	splitted_path = ft_split(*argv, "/");
	pwd = get_pwd(state);
	if (!splitted_path || ft_strvlen(splitted_path) == 0)
	{
		path_value = getenv("HOME");
		ft_do_chdir(state, path_value, pwd, argv);
	}
	while (splitted_path && splitted_path[i])
	{
		if (i == 0 && argv[0][0] == '/')
			splitted_path[i] = ft_strjoin_lf(splitted_path[i], "/");
		if (ft_do_chdir(state, splitted_path[i++], pwd, argv))
			break ;
	}
	ft_strvfree(splitted_path);
	return (0);
}
