/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:53:12 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/04 16:22:56 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush/builtin.h"
#include <stdio.h>

void	ft_print_env_export(void)
{
	char	*path_name;
	char	*path_value;
	int		i;
	int		j;

	i = 0;
	while (jop.envp[i])
	{
		j = 0;
		while (jop.envp[i][j] != '=')
			j++;
		path_name = (char *)ft_set_malloc(sizeof(char), j + 1);
		path_value = (char *)ft_set_malloc(
				sizeof(char), ft_strlen(jop.envp[i]) - j + 1);
		ft_strlcpy(path_name, jop.envp[i], j + 1);
		ft_strlcpy(path_value, jop.envp[i] + j + 1, ft_strlen(jop.envp[i]) - j);
		printf("declare -x %s=\"%s\"\n", path_name, path_value);
		free(path_name);
		free(path_value);
		i++;
	}
}

void	ft_update_env_export(char *argv[])
{
	char	**env;
	int		cnt_env_arr;
	int		i;

	cnt_env_arr = ft_cnt_arg(jop.envp);
	env = (char **)ft_set_malloc(sizeof(char *), cnt_env_arr + 2);
	i = 0;
	if (ft_check_arg_form(argv))
	{
		while (jop.envp[i] && i < cnt_env_arr)
		{
			env[i] = ft_strdup(jop.envp[i]);
			i++;
		}
		env[i] = ft_strdup(argv[1]);
		// ft_free_arr(jop.envp); //test할때는 주석처리 => 할당을 어떻게 하냐에 따라 달라집니다.
		jop.envp = env;
	}
	return ;
}

int	builtin_export(t_state *state, int argc, char *argv[])
{
	if (ft_cnt_arg(argv) == 1)
		ft_print_env_export();
	else if (ft_cnt_arg(argv) >= 2)
		ft_update_env_export(argv);
	return (0);
}
