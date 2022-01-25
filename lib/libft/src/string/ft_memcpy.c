/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:50:14 by SSONG             #+#    #+#             */
/*   Updated: 2021/11/05 00:39:43 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*iter;

	iter = dst;
	while (n > 0)
	{
		*iter = *(unsigned char *)src;
		++iter;
		++src;
		--n;
	}
	return (dst);
}
