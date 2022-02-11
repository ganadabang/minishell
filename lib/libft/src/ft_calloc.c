/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 17:36:44 by SSONG             #+#    #+#             */
/*   Updated: 2022/02/10 21:54:34 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	void	*s;
	size_t	i;

	s = (void *)malloc(count * size);
	if (s == NULL)
		return (NULL);
	p = s;
	while (count > 0)
	{
		i = size;
		while (i-- > 0)
			*(char *)p++ = '\0';
		--count;
	}
	return (s);
}
