/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 20:28:18 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/25 00:57:15 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

static int	get_count(const char *input, const char *sep)
{
	int	count;

	count = 0;
	while (*input)
	{
		++count;
		input += strspn(input, sep);
		input += strcspn(input, sep);
	}
	return (count);
}

static void	cleanup_tokarr(char **tokarr, int count)
{
	int	i;

	i = -1;
	while (++i < count)
		free(tokarr[i]);
	free(tokarr);
}

static char	**fill_tokarr(const char *input, const char *sep, char **tokarr)
{
	char	*token;
	char	*copy;
	int		i;
	
	if (!tokarr)
		return (NULL);
	copy = strdup(input);
	token = strtok(copy, sep);
	i = 0;
	while (token)
	{
		tokarr[i] = strdup(token);
		if (!tokarr[i])
		{
			cleanup_tokarr(tokarr, i);
			tokarr = NULL;
			break ;
		}
		token = strtok(NULL, sep);
		++i;
	}
	free(copy);
	return (tokarr);
}

char	**init_tokarr(const char *input, const char *sep)
{
	char	**tokarr;
	int		count;
	
	if (!input)
		return (NULL);
	count = get_count(input, sep);
	tokarr = (char **)calloc(count + 1, sizeof(char *));
	if (!tokarr)
		return (NULL);
	return (tokarr);
}

char	**ft_split(const char *input, const char *sep)
{
	return (fill_tokarr(input, sep, init_tokarr(input, sep)));
}
