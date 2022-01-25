/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 07:20:35 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/11/04 20:05:33 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned	int	conv_to_abs(int n)
{
	unsigned int	n_abs;

	if (n < 0)
		n_abs = n * -1;
	else
		n_abs = n;
	return (n_abs);
}

static unsigned	int	get_len(unsigned int n)
{
	if (n >= 0 && n < 10)
		return (1);
	return (1 + get_len(n / 10));
}

static char	*conv_abs_to_str(char *str, unsigned int abs)
{
	if (str == NULL)
		return (NULL);
	if (abs == 0)
		return (str);
	else
		*(--str) = abs % 10 + '0';
	return (conv_abs_to_str(str, abs / 10));
}

char	*ft_itoa(int n)
{
	unsigned int	abs;
	unsigned int	len;
	char			is_minus;
	char			*str;

	abs = conv_to_abs(n);
	len = get_len(abs);
	is_minus = 0;
	if (n < 0)
		is_minus = 1;
	str = ft_calloc(is_minus + len + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (abs == 0)
	{
		*str = '0';
		return (str);
	}
	if (is_minus == 1)
		*str = '-';
	return (conv_abs_to_str(str + is_minus + len, abs) - is_minus);
}
