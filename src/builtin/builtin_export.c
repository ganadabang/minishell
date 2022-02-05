/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:53:12 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/05 17:15:02 by gpaeng           ###   ########.fr       */
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
		ft_strlcpy(path_value, state->envp[i] + j + 1,
			ft_strlen(state->envp[i]) - j);
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
		state->envp = env;
	}
	return ;
}

int	builtin_export(t_state *state, int argc, char *argv[])
{
	if (argc == 1)
		ft_print_env_export(state);
	else if (argc >= 2)
		ft_update_env_export(state, argv);
	return (0);
}
