/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 20:35:12 by SSONG             #+#    #+#             */
/*   Updated: 2022/01/25 00:46:36 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n > 0 && *(unsigned char *)s != (unsigned char)c)
	{
		++s;
		--n;
	}
	if (n < 0)
	{
		return (NULL);
	}
	return ((void *)s);
}
