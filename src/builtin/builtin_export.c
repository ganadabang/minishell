/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:53:12 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/04 17:24:31 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"
#include <stdio.h>

void	ft_print_env_export(t_state *state)
{
	char	*path_name;
	char	*path_value;
	int		i;
	int		j;

	i = 0;
	while (state->envp[i])
	{
		j = 0;
		while (state->envp[i][j] != '=')
			j++;
		path_name = (char *)ft_set_malloc(sizeof(char), j + 1);
		path_value = (char *)ft_set_malloc(
				sizeof(char), ft_strlen(state->envp[i]) - j + 1);
		ft_strlcpy(path_name, state->envp[i], j + 1);
		ft_strlcpy(path_value, state->envp[i] + j + 1, ft_strlen(state->envp[i]) - j);
		printf("declare -x %s=\"%s\"\n", path_name, path_value);
		free(path_name);
		free(path_value);
		i++;
	}
}

void	ft_update_env_export(t_state *state, char *argv[])
{
	char	**env;
	int		cnt_env_arr;
	int		i;

	cnt_env_arr = ft_cnt_arg(state->envp);
	env = (char **)ft_set_malloc(sizeof(char *), cnt_env_arr + 2);
	i = 0;
	if (ft_check_arg_form(argv))
	{
		while (state->envp[i] && i < cnt_env_arr)
		{
			env[i] = ft_strdup(state->envp[i]);
			i++;
		}
		env[i] = ft_strdup(argv[1]);
		ft_free_arr(state->envp); //test할때는 주석처리 => 할당을 어떻게 하냐에 따라 달라집니다.
		state->envp = env;
	}
	return ;
}

int	builtin_export(t_state *state, int argc, char *argv[])
{
	if (ft_cnt_arg(argv) == 1)
		ft_print_env_export(state);
	else if (ft_cnt_arg(argv) >= 2)
		ft_update_env_export(state, argv);
	return (0);
}
