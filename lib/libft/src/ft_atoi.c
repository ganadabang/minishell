/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 16:16:40 by SSONG             #+#    #+#             */
/*   Updated: 2021/11/05 04:06:41 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned int	val;
	int				sign;

	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
	{
		++str;
	}
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		sign = 44 - *str;
		++str;
	}
	val = 0;
	while (*str >= '0' && *str <= '9')
	{
		val = val * 10 + *str - '0';
		++str;
	}
	return (sign * val);
}
