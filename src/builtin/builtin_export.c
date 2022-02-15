/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:53:12 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/15 21:00:15 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libfthx.h"
#include "mush/builtin.h"

//To be removed
#include <string.h>

char	**env_deepcpy(t_state *state)
{
	char	**env;
	int		cnt_env_arr;
	size_t	i;
	size_t	j;
	size_t	idx;
	char	*a;
	char	*b;

	cnt_env_arr = ft_cnt_arg(state->envp);
	env = (char **)ft_set_malloc(sizeof(char *), cnt_env_arr + 1);
	i = 0;
	while (cnt_env_arr-- > 0 && state->envp[cnt_env_arr])
	{
		j = 0;
		while (state->envp[j + 1])
		{
			idx = ft_strchrspn(state->envp[j], '=');
			a = strndup(state->envp[j], idx);
			idx = ft_strchrspn(state->envp[j+1], '=');
			b = strndup(state->envp[j+1], idx);
			printf("before: %s  %s\n", state->envp[j], state->envp[j+1]);
			if (ft_strcmp(a, b) > 0)
				ft_strswap(&state->envp[j], &state->envp[j+1]);
			free(a);
			free(b);
			printf("after: %s  %s\n", state->envp[j], state->envp[j+1]);
			j++;
		}
		i--;
	}
	return (env);
}

void	ft_print_env_export(t_state *state)
{
	char	**state_cpy;
	char	*path_name;
	char	*path_value;
	int		i;
	int		j;
	// char	*ptr;

	i = 0;
	state_cpy = env_deepcpy(state);
	bubble_sort_envp(state_cpy);
	while (state_cpy[i])
	{
		j = ft_strchrspn(state->envp[i], '=');
		path_name = strndup(state->envp[i], j);
		path_value = strndup(state->envp[i]+j+1, ft_strlen(state->envp[i]) - j);
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
