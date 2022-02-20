/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 23:16:29 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 03:29:10 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft/io.h"

int	ft_dputnbr(int fd, int n)
{
	char		buf[11];
	long long	lnum;
	size_t		i;

	lnum = n;
	if (lnum < 0)
		lnum = -lnum;
	i = 10;
	while (lnum >= 10)
	{
		buf[--i] = '0' + lnum % 10;
		lnum /= 10;
	}
	buf[--i] = '0' + lnum % 10;
	if (n < 0)
		buf[--i] = '-';
	return (write(fd, &buf[i], 10 - i));
}
