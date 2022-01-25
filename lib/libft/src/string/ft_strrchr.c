/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 14:00:47 by SSONG             #+#    #+#             */
/*   Updated: 2022/01/25 13:50:33 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

/*
 * TODO: TEST
 */

char	*ft_strrchr(const char *s1, int ch)
{
	char	*s;

	s = (char *)s1 + ft_strlen(s1);
	while (*s != ch)
	{
		if (s == s1)
			return (NULL);
		--s;
	}
	return (s);
}
