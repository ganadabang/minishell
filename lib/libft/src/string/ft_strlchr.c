/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:03:56 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/10 13:04:11 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

int 	ft_strlchr(char *str, int c) 
{
	size_t idx;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] == (char)c)
			return (idx);
		idx++;
	}
	return (idx);
}