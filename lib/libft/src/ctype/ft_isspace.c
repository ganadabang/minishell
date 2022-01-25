/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 21:27:30 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/25 01:21:08 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ctype.h"

int	ft_isspace(int c)
{
	return (((unsigned char)c >= 0x9 && (unsigned char)c <= 0xd)
			|| (unsigned char)c == 0x20);
}
