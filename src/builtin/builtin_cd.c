/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:30:14 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/10 21:08:48 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdio.h>
#include "mush.h"

void	ft_update_env(t_state *state, char *path_n, char *path_v)
{
	int		i;
	int		j;
	char	*path;
	char	*path_name;

	i = 0;
	while (state->envp[i])
	{
		j = ft_strchrspn(state->envp[i], '=');
		if (ft_strncmp(state->envp[i], path_n, j) == 0)
		{
			path_name = ft_strndup(state->envp[i], j+1);
			path = ft_strjoin(path_name, path_v);
			state->envp[i] = path;
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
		pwd = getenv(path_n);
		return (pwd);
	}
	pwd = ft_strdup(buffer);
	return (pwd);
}

int	ft_do_chdir(t_state *state, char *path_v, char *oldpwd, char **argv)
{
	struct stat	file_buffer;
	char		*pwd;
	int			file_status;

	if (chdir(path_v) == -1)
	{
		chdir(oldpwd);
		file_status = stat(*argv, &file_buffer);
		if (file_status == -1 && ft_strncmp(argv[0], "-", 1))
			printf("mush: cd: %s No such file or directory\n", argv[0]);
		else if (file_status == 0)
			printf("mush: cd: %s Not a directory", argv[0]);
		return (1);
	}
	pwd = ft_get_pwd("PWD");
	ft_update_env(state, "PWD", pwd);
	ft_update_env(state, "OLDPWD", oldpwd);
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
	pwd = state->pwd;
	if (!splitted_path || ft_cnt_arg(splitted_path) == 0)
	{
		path_value = getenv("HOME");
		ft_do_chdir(state, path_value, pwd, argv);
	}
	while (splitted_path && splitted_path[i])
	{
		if (i == 0 && argv[0][0] == '/')
			ft_add_path(&splitted_path[i], "/");
		if (ft_do_chdir(state, splitted_path[i], pwd, argv))
			break ;
		i++;
	}
	ft_free_arr(splitted_path);
	return (0);
}
