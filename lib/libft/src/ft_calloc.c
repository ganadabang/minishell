/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 17:36:44 by SSONG             #+#    #+#             */
/*   Updated: 2021/11/05 04:02:21 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	void	*s;
	size_t	i;

	s = (void *)malloc(count * size);
	if (s == NULL)
	{
		return (NULL);
	}
	p = s;
	while (count > 0)
	{
		i = size;
		while (i > 0)
		{
			*(char *)p = '\0';
			++p;
			--i;
		}
		--count;
	}
	return (s);
}
