/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 23:10:08 by SSONG             #+#    #+#             */
/*   Updated: 2022/01/25 13:50:33 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

size_t	ft_strlen(const char *str)
{
	const char	*s;

	s = str;
	while (*str)
	{
		++str;
	}
	return (str - s);
}
