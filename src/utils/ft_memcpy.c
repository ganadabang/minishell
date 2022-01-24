/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:30:40 by gpaeng            #+#    #+#             */
/*   Updated: 2022/01/24 23:41:07 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush/builtin.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dtmp;
	const char	*stmp;

	if (!dest && !src)
		return (0);
	dtmp = dest;
	stmp = src;
	while (n--)
	{
		*dtmp++ = *stmp++;
	}
	return (dest);
}
