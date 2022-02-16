/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mush_env_realloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:31:06 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/17 02:44:41 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "mush/builtin.h"

void	mush_env_realloc(t_state *state)
{
	char	**env;
	int		len;

	len = ft_strvlen(state->envp);
	env = (char **)realloc(state->envp, len + 2);
	if (env == NULL)
		mush_fatal("malloc");
	free(state->envp);
	state->envp = env;
	return ;
}
