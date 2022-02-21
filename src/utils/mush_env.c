/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mush_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 03:10:38 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 17:19:59 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "mush.h"

static int	join_key_value(char **str_ref, char *name, char *value)
{
	char	*nul;
	char	*str;

	*str_ref = NULL;
	str = (char *)malloc((ft_strlen(name) + ft_strlen(value) + 2) \
		* sizeof(char));
	if (str == NULL)
		return (-1);
	nul = ft_stpcpy(str, name);
	*nul = '=';
	ft_memcpy(++nul, value, ft_strlen(value));
	*str_ref = str;
	return (0);
}

void	mush_set_env(t_state *state, char *name, char *value)
{
	int		index;
	char	*str;
	char	*join;

	if (value == NULL)
	{
		join = ft_strjoin(name, "=");
		mush_put_env(state, join);
		free(join);
		return ;
	}
	if (join_key_value(&str, name, value) < 0)
		return ;
	index = mush_get_env_index(state, name);
	if (index < 0)
	{
		mush_put_env(state, str);
		free(str);
		return ;
	}
	free(state->envlist.data[index]);
	state->envlist.data[index] = str;
	return ;
}

int	mush_get_env_index(t_state *state, char *name)
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
		cmp_len = ft_strcspn(vars[i], "=");
		if (ft_memcmp(vars[i], name, cmp_len) == 0)
			return (i);
		++i;
	}
	return (-1);
}

char	*mush_get_env(t_state *state, char *name)
{
	int		index;
	char	*value;

	if (ft_memcmp(name, "?", 2) == 0)
		return (state->last_status);
	index = mush_get_env_index(state, name);
	if (index < 0)
		return (NULL);
	value = (char *)state->envlist.data[index];
	value += ft_strcspn(value, "=");
	if (*value == '=')
		++value;
	return (value);
}

void	mush_put_env(t_state *state, char *str)
{
	char	*name;
	int		name_len;
	int		index;

	name_len = ft_strcspn(str, "=");
	name = ft_strndup(str, name_len);
	index = mush_get_env_index(state, name);
	free(name);
	if (index < 0)
	{
		hx_array_push(&state->envlist, ft_strdup(str));
		return ;
	}
	if (str[name_len] == '\0')
		return ;
	free(state->envlist.data[index]);
	state->envlist.data[index] = ft_strdup(str);
	return ;
}
