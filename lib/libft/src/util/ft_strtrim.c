/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 19:03:38 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/25 13:51:28 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * TODO: TEST
 */
char	*ft_strtrim(const char *s1, char const *set)
{
	char	*s;

	if (*set == '\0')
	{
		return (ft_strdup(s1));
	}
	while (*s1 != '\0' && ft_strchr(set, *s1) != NULL)
	{
		++s1;
	}
	s = (char *)s1 + ft_strlen(s1);
	while (s != s1 && ft_strchr(set, *s) != NULL)
	{
		--s;
	}
	return (ft_substr(s1, 0, s - s1));
}
