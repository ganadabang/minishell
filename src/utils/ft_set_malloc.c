/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:35:54 by gpaeng            #+#    #+#             */
/*   Updated: 2022/01/24 23:41:07 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush/builtin.h"

void	*ft_memset(void *dest, int c, size_t n)
{
	char	*tmp;

	tmp = dest;
	while (n-- > 0)
	{
		*tmp++ = c;
	}
	return (dest);
}

void	*ft_set_malloc(size_t nmemb, int size)
{
	char	*arr;

	arr = (void *)malloc(nmemb * size);
	if (!(arr))
		return (0);
	ft_memset(arr, 0, nmemb * size);
	return (arr);
}
