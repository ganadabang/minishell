/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 14:51:45 by SSONG             #+#    #+#             */
/*   Updated: 2022/01/25 13:50:33 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

/*
 * TODO: TEST
 */
char	*ft_strnstr(const char *str, const char *substr, size_t len)
{
	char	*s;
	size_t	sublen;
	
	sublen = ft_strlen(substr);
	len -= sublen;
	while (len > 0)
	{
		s = ft_strchr(str, *substr);
		len -= s - str;
		if (s == NULL || len < 0)
		{
			return (NULL);
		}
		if (ft_strncmp(s, substr, sublen) == 0)
		{
			return (s);
		}
		str = s + 1;
		--len;
	}
	return (NULL);
}
