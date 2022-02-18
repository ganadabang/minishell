/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mush_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 03:10:38 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/19 03:23:49 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libfthx.h"
#include "mush.h"

static int	mush_get_env_index(t_state *state, char *key)
{
	char		**vars;
	size_t		cmp_len;
	size_t		len;
	size_t		i;

	vars = (char **)state->envlist.data;
	len = state->envlist.len;
	i = 0;
	while (i < len)
	{
		cmp_len = strcspn(vars[i], "=");
		if (memcmp(vars[i], key, cmp_len) == 0)
			return (i);
		++i;
	}
	return (-1);
}

char	*mush_get_env(t_state *state, char *key)
{
	int		index;
	char	*value;

	if (memcmp(key, "?", 2) == 0)
		return (state->last_status);
	index = mush_get_env_index(state, key);
	if (index < 0)
		return (NULL);
	value = (char *)state->envlist.data[index];
	value += strcspn(value, "=");
	if (*value == '=')
		++value;
	return (value);
}

void	mush_set_env(t_state *state, char *key, char *value)
{
	int		index;
	char	*str;
	char	*nul;
	char	*join;

	if (value == NULL)
	{
		join = ft_strjoin(key, "=");
		mush_put_env(state, join);
		free(join);
		return ;
	}
	str = (char *)malloc((strlen(key) + strlen(value) + 2) * sizeof(char));
	nul = stpcpy(str, key);
	*nul = '=';
	strcpy(++nul, value);
	index = mush_get_env_index(state, key);
	if (index < 0)
	{
		mush_put_env(state, str);
		free(str);
		return ;
	}
	free(state->envlist.data[index]);
	state->envlist.data[index] = str;
}

void	mush_put_env(t_state *state, char *str)
{
	char	*key;
	int		key_len;
	int		index;

	key_len = strcspn(str, "=");
	key = strndup(str, key_len);
	index = mush_get_env_index(state, key);
	free(key);
	if (index < 0)
	{
		hx_array_push(&state->envlist, strdup(str));
		return ;
	}
	if (str[key_len] != '=')
		return ;
	free(state->envlist.data[index]);
	state->envlist.data[index] = strdup(str);
	return ;
}

void	mush_unset_env(t_state *state, char *key)
{
	int		index;
	char	*tofree;

	index = mush_get_env_index(state, key);
	if (index < 0)
		return ;
	tofree = (char *)hx_array_pop_index(&state->envlist, index);
	free(tofree);
	return ;
}

