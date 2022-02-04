/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:49:34 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/04 16:23:09 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush/builtin.h"
#include <stdio.h>

int	ft_check_env(char *argv)
{
	int	i;

	i = 0;
	while (jop.envp[i])
	{
		if (!(ft_strncmp(jop.envp[i], argv, ft_strlen(argv))))
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

void	ft_remove_env(int env_line)
{
	char	**env;
	int		cnt_env_arr;
	int		envp_i;
	int		i;

	cnt_env_arr = ft_cnt_arg(jop.envp);
	env = (char **)ft_set_malloc(sizeof(char *), cnt_env_arr);
	i = 0;
	envp_i = 0;
	while (envp_i < cnt_env_arr)
	{
		if (envp_i != env_line)
		{
			env[i] = ft_strdup(jop.envp[envp_i]);
			i++;
		}
		envp_i++;
	}
	// ft_free_arr(jop.envp);
	jop.envp = env;
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
		env_line = ft_check_env(argv[i]);
		if (ft_check_args_unset(*argv[i]))
		{
			printf("minishell: unset: %s not a valid identifier", argv[i]);
			return (1);
		}
		if (env_line != -1)
			ft_remove_env(env_line);
		i++;
	}
	return (0);
}
