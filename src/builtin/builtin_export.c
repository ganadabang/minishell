/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:53:12 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/10 14:03:52 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"
#include <stdio.h>

void	ft_strswap(char **str1, char **str2)
{
	char *tmp;

	if (!str1 || !str2)
		return ;
	tmp = ft_strdup(*str1);
	*str1 = ft_strdup(*str2);
	*str2 = tmp;
}

int	bubble_sort_envp(t_state *state, int i, int j)
{
	char *a;
	char *b;
	int idx;

	i = ft_cnt_arg(state->envp);
	while (i)
	{
		while (state->envp[j + 1])
		{
			idx = ft_strlchr(state->envp[j], '=');
			a = ft_strndup(state->envp[j], idx);
			idx = ft_strlchr(state->envp[j+1], '=');
			b = ft_strndup(state->envp[j+1], idx);
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
	return (0);
}

void	ft_print_env_export(t_state *state)
{
	char	*path_name;
	char	*path_value;
	int		i;
	int		j;

	i = 0;
	bubble_sort_envp(state, 0, 0);
	while (state->envp[i])
	{
		j = ft_strlchr(state->envp[i], '=');
		path_name = ft_strndup(state->envp[i], j);
		path_value = ft_strndup(state->envp[i]+j+1, ft_strlen(state->envp[i]) - j);
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
		// free(state->envp);
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
