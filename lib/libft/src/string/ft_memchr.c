/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 20:35:12 by SSONG             #+#    #+#             */
/*   Updated: 2022/01/25 13:50:33 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

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
