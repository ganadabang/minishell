/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_expn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:50:13 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 02:47:09 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "sys/errno.h"
#include "sys/stat.h"
#include "libfthx.h"
#include "mush/parser.h"
char	*exec_expn_cmd(t_state *state_ref, char *name)
{
	char	*slash_name;
	char	*path_cmd;
	char	*path;
	char	**pathv;
	size_t	i;

	if (*name == '\0')
		return (NULL);
	path = mush_get_env(state_ref, "PATH");
	if (ft_strchr(name, '/') != NULL || path == NULL)
		return (name);
	slash_name = ft_strjoin("/", name);
	if (slash_name == NULL)
		mush_fatal("malloc");
	free(name);
	pathv = ft_split(path, ":");
	if (pathv == NULL)
		mush_fatal("malloc");
	path_cmd = NULL;
	i = 0;
	while (pathv[i] != NULL)
	{
		path_cmd = ft_strjoin(pathv[i], slash_name);
		free(pathv[i++]);
		stat(path_cmd, NULL);
		if (errno != ENOENT)
			break ;
		free(path_cmd);
		path_cmd = NULL;
	}
	while (pathv[i] != NULL)
		free(pathv[i++]);
	free(pathv);
	free(slash_name);
	return (path_cmd);
}

size_t	exec_expn_buffer_putenv(t_state *state_ref, t_buf *buffer, char *word)
{
	char	*key;
	char	*value;
	size_t	key_len;
	size_t	value_len;

	key_len = ft_strcspn(word, "'\"$ \t\n");
	key = ft_strndup(word, key_len);
	value = mush_get_env(state_ref, key);
	free(key);
	value_len = 0;
	if (value != NULL)
		value_len = ft_strlen(value);
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
	while (1)
	{
		if (word[i] == '\'' && !double_quoted)
			single_quoted = !single_quoted;
		else if (word[i] == '\"' && !single_quoted)
			double_quoted = !double_quoted;
		else if (word[i] == '$' && !single_quoted)
			i += exec_expn_buffer_putenv(state_ref, buffer, &word[i + 1]);
		else
			hx_buffer_putchar(buffer, word[i]);
		if (word[++i] == '\0')
			break ;
	}
	return (hx_buffer_withdraw(buffer));
}

void	exec_expn_argv(t_state *state_ref, t_array *exec_argv)
{
	t_buf	buffer;
	char	**argv;
	char	*tokfree;
	size_t	len;
	size_t	i;

	len = exec_argv->len;
	if (len == 0)
		return ;
	ft_memset(&buffer, 0, sizeof(t_buf));
	argv = (char **)exec_argv->data;
	i = 0;
	while (i < len)
	{
		tokfree = argv[i];
		argv[i] = exec_expn_word(state_ref, &buffer, argv[i]);
		if (argv[i] == NULL)
		{
			argv[i] = ft_strdup("");
			if (argv[i] == NULL)
				mush_fatal("malloc");
		}
		free(tokfree);
		++i;
	}
	hx_buffer_cleanup(&buffer);
	return ;
}
