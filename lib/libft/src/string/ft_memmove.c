/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 17:54:15 by SSONG             #+#    #+#             */
/*   Updated: 2022/02/11 14:06:05 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*iter;
	int				flag;

	flag = 1;
	iter = dst;
	if (dst > src)
	{
		iter += n - 1;
		src += n - 1;
		flag = -1;
	}
	while (n > 0)
	{
		*iter = *(unsigned char *)src;
		iter += flag;
		src += flag;
		--n;
	}
	return (dst);
}
