/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:30:14 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/04 16:22:03 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdio.h>
#include "mush/builtin.h"

void	ft_update_env(char *path_n, char *path_v)
{
	int		i;
	int		j;
	char	*path;
	char	*path_name;

	i = 0;
	while (jop.envp[i])
	{
		j = 0;
		while (jop.envp[i][j] != '=')
			j++;
		if (ft_strncmp(jop.envp[i], path_n, j) == 0)
		{
			path_name = (char *)ft_set_malloc(sizeof(char), j);
			ft_strlcpy(path_name, jop.envp[i], j + 2);
			path = ft_strjoin(path_name, path_v);
			// free(jop.envp[i]);
			jop.envp[i] = path;
		}
		i++;
	}
}

char	*ft_get_pwd(char *path_n)
{
	char	buffer[4096];
	char	*pwd;

	if (getcwd(buffer, 4096) == 0)
	{
		pwd = ft_get_env(path_n);
		return (pwd);
	}
	pwd = ft_strdup(buffer);
	return (pwd);
}

int	ft_do_chdir(char *path_v, char *oldpwd, char **argv)
{
	struct stat	file_buffer;
	char		*pwd;
	int			file_status;

	if (chdir(path_v) == -1)
	{
		chdir(oldpwd);
		file_status = stat(*argv, &file_buffer);
		if (file_status == -1 && ft_strncmp(argv[0], "-", 1))
			printf("minishell: cd: %s No such file or directory\n", argv[0]);
		return (1);
	}
	pwd = ft_get_pwd("PWD");
	ft_update_env("PWD", pwd);
	ft_update_env("OLDPWD", oldpwd);
	free(pwd);
	return (0);
}

int	ft_check_args_cd(char *argv[])
{
	char	*path_value;
	char	*pwd;

	if (ft_cnt_arg(argv) > 1)
	{
		printf("minishell: cd: too many arguments\n");
		return (0);
	}
	else if (ft_cnt_arg(argv) == 1)
	{
		pwd = ft_get_pwd("PWD");
		if (ft_strncmp(argv[0], "-", 1) == 0)
		{
			path_value = ft_get_env("OLDPWD");
			ft_do_chdir(path_value, pwd, argv);
			printf("%s\n", pwd);
			return (0);
		}
		free(pwd);
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
	if (!ft_check_args_cd(argv))
		return (1);
	splitted_path = ft_split(*argv, "/");
	pwd = ft_get_pwd("PWD");
	if (!splitted_path || ft_cnt_arg(argv) == 0)
	{
		path_value = ft_get_env("HOME");
		ft_do_chdir(path_value, pwd, argv);
	}
	while (splitted_path && splitted_path[i])
	{
		ft_add_path(&splitted_path[i], "/");
		if (ft_do_chdir(splitted_path[i], pwd, argv))
			break ;
		i++;
	}
	free(pwd);
	ft_free_arr(splitted_path);
	return (0);
}
