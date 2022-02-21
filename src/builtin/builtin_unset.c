/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:49:34 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/21 16:57:58 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libfthx.h"
#include "mush/builtin.h"

static void	mush_unset_env(t_state *state, char *name)
{
	int		index;
	char	*tofree;

	index = mush_get_env_index(state, name);
	if (index < 0)
		return ;
	tofree = (char *)hx_array_pop_index(&state->envlist, index);
	free(tofree);
	return ;
}

int	builtin_unset(t_state *state, int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!mush_is_valid_name(argv[i]))
		{
			ft_dputs(2, "mush: unset: `");
			ft_dputs(2, argv[i]);
			ft_dputs(2, "': not a valid identifier\n");
		}
		else
			mush_unset_env(state, argv[i]);
		++i;
	}
	return (0);
}
