/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stpcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:11:53 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 17:18:31 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

char	*ft_stpcpy(char *dst, const char *src)
{
	size_t	len;

	len = ft_strlen(src);
	ft_memcpy(dst, src, len + 1);
	return (dst + len);
}
