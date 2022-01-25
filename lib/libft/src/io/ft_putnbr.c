/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 01:25:23 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/25 01:16:51 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"

int	ft_putnbr(int n)
{
	if (n < 0)
	{
		return (ft_putc('-') + ft_puts(ft_itoa(n)));
	}
	return (ft_puts(ft_itoa(n)));
}
