/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:03:56 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/10 21:02:21 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_chrspn(const char *str, int c) 
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			break ;
		++i;
	}
	return (i);
}
