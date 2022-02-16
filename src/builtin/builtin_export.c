/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:53:12 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/17 03:13:26 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libfthx.h"
#include "mush/builtin.h"

//To be removed
#include <string.h>

void	ft_print_env_export(t_state *state)
{
	char	**state_cpy;
	char	*path_name;
	char	*path_value;
	int		i;
	int		j;

	i = 0;
	state_cpy = (char **)realloc(state->envp, ft_strvlen(state->envp) + 1);
	ft_strvsort(state_cpy);
	while (state_cpy[i])
	{
		j = ft_chrspn(state->envp[i], '=');
		path_name = ft_strndup(state->envp[i], j);
		path_value = ft_strndup(state->envp[i] + j + 1,
				ft_strlen(state->envp[i]) - j);
		printf("declare -x %s=\"%s\"\n", path_name, path_value);
		free(path_name);
		free(path_value);
		free(state_cpy[i]);
		i++;
	}
	free(state_cpy);
}

void	ft_update_env_export(t_state *state, char *argv[])
{
	char	**env;
	int		cnt_env_arr;
	int		i;

	cnt_env_arr = ft_strvlen(state->envp);
	env = (char **)ft_calloc(cnt_env_arr + 2, sizeof(char *));
	i = 0;
	if (mush_regex(argv))
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
