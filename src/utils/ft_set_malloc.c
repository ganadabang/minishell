/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:35:54 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/15 20:57:58 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	**ft_set_malloc(size_t nmemb, int size)
{
	void	**arr;

	arr = (void **)malloc(nmemb * size);
	if (!(arr))
		return (0);
	ft_memset(arr, 0, nmemb * size);
	return (arr);
}
