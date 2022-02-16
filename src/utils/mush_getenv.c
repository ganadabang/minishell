/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mush_getenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 23:39:14 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/17 04:13:16 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mush.h"

char	*mush_getenv(t_state *state, char *key)
{
	char	**envp;
	size_t	key_len;
	size_t	i;

	if (ft_memcmp(key, "PWD", 4) == 0)
		return (state->pwd);
	if (ft_memcmp(key, "OLDPWD", 7) == 0)
		return (state->old_pwd);
	if (ft_memcmp(key, "?", 2) == 0)
		return (state->last_status);
	envp = state->envp;
	key_len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_memcmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
			return (&envp[i][key_len + 1]);
		++i;
	}
	return (NULL);
}
