/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 20:28:18 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/12 21:01:28 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	get_count(const char *input, const char *sep)
{
	int	count;

	count = 0;
	while (*input)
	{
		++count;
		input += ft_strspn(input, sep);
		input += ft_strcspn(input, sep);
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
	copy = ft_strdup(input);
	token = ft_strtok(copy, sep);
	i = 0;
	while (token)
	{
		tokarr[i] = ft_strdup(token);
		if (!tokarr[i])
		{
			cleanup_tokarr(tokarr, i);
			tokarr = NULL;
			break ;
		}
		token = ft_strtok(NULL, sep);
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
	tokarr = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!tokarr)
		return (NULL);
	return (tokarr);
}

char	**ft_split(const char *input, const char *sep)
{
	return (fill_tokarr(input, sep, init_tokarr(input, sep)));
}
