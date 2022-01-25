/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 17:25:26 by SSONG             #+#    #+#             */
/*   Updated: 2022/01/25 01:22:38 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ctype.h"

int	ft_toupper(int c)
{
	if ((unsigned char)c >= 0x61 && (unsigned char)c <= 0x7a)
		return ((unsigned char)c + 0x20);
	return ((unsigned char)c);
}
