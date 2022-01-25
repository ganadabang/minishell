/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 23:16:29 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/25 23:43:58 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"

int	ft_dputnbr(int fd, int n)
{
	if (fd < 0)
		return (-1);
	if (n < 0)
	{
		return (ft_dputchar(fd, '-') + ft_dputs(fd, ft_itoa(n)));
	}
	return (ft_dputs(fd, ft_itoa(n)));
}
