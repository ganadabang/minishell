/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_deepcpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:31:06 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/16 18:48:53 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "mush/builtin.h"

char	**env_deepcpy(t_state *state)
{
	char	**env;
	int		cnt_env_arr;
	int		i;

	cnt_env_arr = ft_cnt_arg(state->envp);
	env = (char **)ft_set_malloc(sizeof(char *), cnt_env_arr + 1);
	i = 0;
	while (cnt_env_arr-- > 0 && state->envp[cnt_env_arr])
	{
		env[i] = ft_strdup(state->envp[i]);
		i++;
	}
	env[i] = 0;
	return (env);
}