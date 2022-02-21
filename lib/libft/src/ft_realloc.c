/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 00:37:47 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 17:22:43 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_realloc(void *ptr, size_t cpy_size, size_t alloc_size)
{
	void	*new;

	new = (void *)malloc(alloc_size);
	if (new == NULL)
		return (NULL);
	ft_memset(new, 0, alloc_size);
	ft_memcpy(new, ptr, cpy_size);
	free(ptr);
	return (new);
}
