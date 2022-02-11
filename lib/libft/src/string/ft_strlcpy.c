/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 23:17:19 by SSONG             #+#    #+#             */
/*   Updated: 2022/02/10 21:46:05 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	i;

	if (dst == NULL && src == NULL)
		return (0);
	len = ft_strlen(src);
	if (dst == NULL)
		return (len);
	i = 0;
	while (src[i] != '\0' && dstsize-- > 1)
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = '\0';
	return (len);
}
