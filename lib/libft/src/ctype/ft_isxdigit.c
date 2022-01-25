/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isxdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 21:47:49 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/25 01:21:08 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ctype.h"

int	ft_isxdigit(int c)
{
	return (((unsigned char)c >= 0x41 && (unsigned char)c <= 0x46) \
			|| ((unsigned char)c >= 0x30 && (unsigned char)c <= 0x39) \
			|| ((unsigned char)c >= 0x41 && (unsigned char)c <= 0x5a));
}
