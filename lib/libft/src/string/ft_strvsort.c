/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strvsort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:52:33 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/21 13:44:01 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** bubble sort
*/
void	ft_strvsort(char **str)
{
	int	i;
	int	j;
	int	n;
	int	m;

	j = ft_strvlen(str);
	while (--j)
	{
		i = 0;
		while (i < j)
		{
			n = ft_strcspn(str[i], "=");
			m = ft_strcspn(str[i + 1], "=");
			if (n < m)
				n = m;
			if (ft_memcmp(str[i], str[i + 1], n) > 0)
				ft_swap((void **)&str[i], (void **)&str[i + 1]);
			i++;
		}
	}
	return ;
}
