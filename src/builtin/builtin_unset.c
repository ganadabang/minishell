/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:49:34 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/16 15:43:22 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mush/builtin.h"
#include "libfthx.h"

int	ft_check_env(t_state *state, char *str)
{
	int	i;

	i = 0;
	while (state->envp[i])
	{
		if ((ft_strncmp(state->envp[i], str, ft_strlen(str)) > 0))
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
	state->envp = env;
}

int	ft_check_first(char c)
{	
	if (c == '_' || ft_isalpha(c))
		return (0);
	return (1);
}

int	ft_check_all(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] == '_' || ft_isalpha(str[i]) || ft_isdigit(str[i])))
			return (1);
		i++;
	}
	return (0);
}

int	builtin_unset(t_state *state, int argc, char *argv[])
{
	int	i;
	int	env_line;

	i = 1;
	env_line = 0;
	while (argv[i])
	{
		env_line = ft_check_env(state, argv[i]);
		if (ft_check_first(*argv[i]) || ft_check_all(argv[i]))
		{
			printf("mush: unset: %s not a valid identifier\n", argv[i]);
			return (1);
		}
		else if (env_line != -1)
			ft_remove_env(state, env_line);
		i++;
	}
	return (0);
}
