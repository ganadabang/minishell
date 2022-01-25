/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 13:26:28 by SSONG             #+#    #+#             */
/*   Updated: 2021/11/05 03:20:59 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/*
 * TODO: TEST
 */
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
