/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 17:27:07 by SSONG             #+#    #+#             */
/*   Updated: 2022/01/25 13:50:33 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

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
