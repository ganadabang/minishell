/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_expn_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:50:13 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 16:01:30 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "sys/errno.h"
#include "sys/stat.h"
#include "libfthx.h"
#include "mush/parser.h"

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

static int	expn_argv_word(t_state *state, t_buf *buffer, char **word_ref)
{
	char	*tofree;

	tofree = *word_ref;
	*word_ref = exec_expn_word(state, buffer, tofree);
	free(tofree);
	if (*word_ref == NULL)
	{
		*word_ref = ft_strdup("");
		if (*word_ref == NULL)
			return (-1);
	}
	return (0);
}

void	exec_expn_argv(t_state *state_ref, t_array *exec_argv)
{
	t_buf	buffer;
	char	**argv;
	size_t	len;
	size_t	i;

	len = exec_argv->len;
	if (len == 0)
		return ;
	ft_memset(&buffer, 0, sizeof(t_buf));
	argv = (char **)exec_argv->data;
	i = 0;
	while (i < len)
		expn_argv_word(state_ref, &buffer, &argv[i++]);
	hx_buffer_cleanup(&buffer);
	return ;
}
