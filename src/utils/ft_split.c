/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:30:43 by gpaeng            #+#    #+#             */
/*   Updated: 2022/01/24 23:41:07 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush/builtin.h"

static	size_t	ft_cntword(char const *s, char c)
{
	size_t	cnt;

	cnt = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		if (*s && *s != c)
		{
			cnt++;
			while (*s && *s != c)
				s++;
		}
		while (*s && *s == c)
			s++;
	}
	return (cnt);
}

static size_t	ft_lenword(char const *s, char c)
{
	size_t	lenword;

	lenword = 0;
	while (*s && *s++ != c)
		lenword++;
	return (lenword);
}

static	char	*ft_fd_strdup(const char *s, size_t lenword)
{
	char	*arr;
	size_t	idx;

	idx = 0;
	arr = (char *)malloc(sizeof(char) * (lenword + 1));
	if (!(arr))
		return (0);
	while (idx < lenword)
	{
		arr[idx] = s[idx];
		idx++;
	}
	arr[idx] = 0;
	return (arr);
}

static	void	ft_free(char **s, int idx)
{
	while (idx--)
		free(s[idx]);
	free(s);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	cntword;
	size_t	lenword;
	size_t	aidx;

	if (!s)
		return (0);
	cntword = ft_cntword(s, c);
	arr = (char **)malloc(sizeof(char *) * (cntword + 1));
	if (!(arr))
		return (0);
	aidx = 0;
	while (aidx < cntword)
	{
		while (*s && *s == c)
			s++;
		lenword = ft_lenword(s, c);
		arr[aidx] = ft_fd_strdup(s, lenword);
		if (!(arr[aidx]))
		{
			ft_free(arr, aidx - 1);
			return (0);
		}
		aidx++;
		s += lenword;
	}
	arr[cntword] = 0;
	return (arr);
}
