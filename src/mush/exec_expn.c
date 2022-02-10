/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_expn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:50:13 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/09 17:03:12 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "mush.h"

char	*exec_expn_cmd(t_state *state_ref, char *name)
{
	char	*slash_name;
	char	*path_cmd;
	char	*path;
	char	**pathv;
	size_t	i;

	if (strchr(name, '/') != NULL)
		return (name);
	path = getenv("PATH");
	if (path == NULL)
	{
		free(name);
		return (NULL);
	}
	slash_name = ft_strjoin("/", name);
	free(name);
	if (slash_name == NULL)
		return (NULL);
	pathv = ft_split(path, ":");
	i = 0;
	while (pathv[i] != NULL)
	{
		path_cmd = ft_strjoin(pathv[i], slash_name);
		if (access(path_cmd, F_OK) == 0)
			break ;
		free(path_cmd);
		path_cmd = NULL;
		++i;
	}
	free(slash_name);
	ft_free_arr(pathv);
	return (path_cmd);
}

size_t	exec_expn_buffer_putenv(t_state *state_ref, t_buf *buffer, char *word)
{
	char	*key;
	char	*value;
	size_t	key_len;
	size_t	value_len;

	key_len = strcspn(word, "'\"$ \t\n");
	key = strndup(word, key_len);
	// value = getvar(state_ref, key);
	// if (value == NULL)
	// 	value = mush_getenv(state_ref, key);
	value =  getenv(key);
	free(key);
	value_len = 0;
	if (value != NULL)
		value_len = strlen(value);
	hx_buffer_putstr(buffer, value, value_len);
	return (key_len);
}

char	*exec_expn_word(t_state *state_ref, t_buf *buffer, char *word)
{
	int		double_quoted;
	int		single_quoted;
	size_t	i;

	double_quoted = 0;
	single_quoted = 0;
	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '\''  && !double_quoted)
		{
			single_quoted = !single_quoted;
			++i;
		}
		else if (word[i] == '\"' && !single_quoted)
		{
			double_quoted = !double_quoted;
			++i;
		}
		else if (word[i] == '$' && !single_quoted)
		{
			++i;
			i += exec_expn_buffer_putenv(state_ref, buffer, &word[i]);
		}
		else
			hx_buffer_putchar(buffer, word[i++]);
	}
	free(word);
	return (hx_buffer_withdraw(buffer));
}

void	exec_expn_argv(t_state *state_ref, t_array *exec_argv)
{
	t_buf	buffer = {};
	char	**data;
	size_t	len;
	size_t	i;

	data = (char **)exec_argv->data;
	len = exec_argv->len;
	i = 0;
	while (i < len)
	{
		data[i] = exec_expn_word(state_ref, &buffer, data[i]);
		++i;
	}
	hx_buffer_cleanup(&buffer);
	return ;
}
