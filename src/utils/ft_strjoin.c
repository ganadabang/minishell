/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:30:49 by gpaeng            #+#    #+#             */
/*   Updated: 2022/01/11 11:57:36 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		ls1;
	int		ls2;
	char	*arr;

	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	arr = (char *)malloc(sizeof(char) * (ls1 + ls2));
	if (!(arr))
		return (0);
	ft_memcpy(arr, s1, ls1);
	ft_memcpy(arr + ls1, s2, ls2);
	arr[ls1 + ls2] = '\0';
	return (arr);
}
