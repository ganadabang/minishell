/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 10:18:35 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 03:24:42 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*memb;

	memb = (unsigned char *)s;
	while (n-- > 0)
		*memb++ = 0;
}
