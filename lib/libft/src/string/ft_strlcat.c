/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 13:26:28 by SSONG             #+#    #+#             */
/*   Updated: 2022/02/10 20:59:27 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dst == NULL && dstsize == 0)
	{
		return (src_len);
	}
	dst_len = ft_strlen(dst);
	if (dst_len >= dstsize)
	{
		return (dstsize + src_len);
	}
	ft_strlcpy(dst + dst_len, src, dstsize - dst_len);
	return (dst_len + src_len);
}
