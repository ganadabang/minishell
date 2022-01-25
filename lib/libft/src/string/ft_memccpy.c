/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 17:27:07 by SSONG             #+#    #+#             */
/*   Updated: 2021/11/05 00:39:15 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	while (n > 0 && *(unsigned char *)src != (unsigned char)c)
	{
		*(unsigned char *)dst = *(unsigned char *)src;
		++src;
		++dst;
		--n;
	}
	if (n < 0)
	{
		return (NULL);
	}
	return (dst);
}
