/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mush_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 03:10:38 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/19 05:16:31 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libfthx.h"
#include "mush.h"

static int	mush_get_env_index(t_state *state, char *name)
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
		if (memcmp(vars[i], name, cmp_len) == 0)
			return (i);
		++i;
	}
	return (-1);
}

char	*mush_get_env(t_state *state, char *name)
{
	int		index;
	char	*value;

	if (memcmp(name, "?", 2) == 0)
		return (state->last_status);
	index = mush_get_env_index(state, name);
	if (index < 0)
		return (NULL);
	value = (char *)state->envlist.data[index];
	value += strcspn(value, "=");
	if (*value == '=')
		++value;
	return (value);
}

void	mush_set_env(t_state *state, char *name, char *value)
{
	int		index;
	char	*str;
	char	*nul;
	char	*join;

	if (value == NULL)
	{
		join = ft_strjoin(name, "=");
		mush_put_env(state, join);
		free(join);
		return ;
	}
	str = (char *)malloc((strlen(name) + strlen(value) + 2) * sizeof(char));
	nul = stpcpy(str, name);
	*nul = '=';
	strcpy(++nul, value);
	index = mush_get_env_index(state, name);
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
	char	*name;
	int		name_len;
	int		index;

	name_len = strcspn(str, "=");
	name = strndup(str, name_len);
	index = mush_get_env_index(state, name);
	free(name);
	if (index < 0)
	{
		hx_array_push(&state->envlist, strdup(str));
		return ;
	}
	if (str[name_len] != '=')
		return ;
	free(state->envlist.data[index]);
	state->envlist.data[index] = strdup(str);
	return ;
}

int	mush_is_valid_name(char *name)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(name[i]) && name[i] != '_')
		return (0);
	while (name[++i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
	}
	return (1);
}
