/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:49:34 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/04 17:38:47 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"
#include <stdio.h>

int	ft_check_env(t_state *state, char *argv)
{
	int	i;

	i = 0;
	while (state->envp[i])
	{
		if (!(ft_strncmp(state->envp[i], argv, ft_strlen(argv))))
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

void	ft_remove_env(t_state *state, int env_line)
{
	char	**env;
	int		cnt_env_arr;
	int		envp_i;
	int		i;

	cnt_env_arr = ft_cnt_arg(state->envp);
	env = (char **)ft_set_malloc(sizeof(char *), cnt_env_arr);
	i = 0;
	envp_i = 0;
	while (envp_i < cnt_env_arr)
	{
		if (envp_i != env_line)
		{
			env[i] = ft_strdup(state->envp[envp_i]);
			i++;
		}
		envp_i++;
	}
	ft_free_arr(state->envp); 
	state->envp = env;
}

int	ft_check_args_unset(char c)
{
	if (c == '_' || ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

int	builtin_unset(t_state *state, int argc, char *argv[])
{
	int	i;
	int	env_line;

	i = 1;
	env_line = 0;
	// argv++;
	while (argv[i])
	{
		env_line = ft_check_env(state, argv[i]);
		if (ft_check_args_unset(*argv[i]))
		{
			printf("mush: unset: %s not a valid identifier", argv[i]);
			return (1);
		}
		if (env_line != -1)
			ft_remove_env(state, env_line);
		i++;
	}
	return (0);
}
