/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 17:14:02 by SSONG             #+#    #+#             */
/*   Updated: 2022/01/25 01:21:34 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ctype.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) \
		|| ((unsigned char)c >= '0' && (unsigned char)c <= '9'));
}
