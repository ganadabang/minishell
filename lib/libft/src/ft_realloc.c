/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 00:37:47 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 00:48:38 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new;

	new = (void  *)malloc(size);
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, ptr, size);
	free(ptr);
	return (new);
}
