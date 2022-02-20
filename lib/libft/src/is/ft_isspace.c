/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 21:27:30 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 03:28:01 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/is.h"

int	ft_isspace(int c)
{
	return (((unsigned char)c >= 0x9 && (unsigned char)c <= 0xd)
			|| (unsigned char)c == 0x20);
}
