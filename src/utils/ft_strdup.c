/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:30:47 by gpaeng            #+#    #+#             */
/*   Updated: 2022/01/06 15:08:28 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

char	*ft_strdup(const char *str)
{
	char	*arr;

	arr = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!(arr))
		return (0);
	ft_memcpy(arr, str, ft_strlen(str) + 1);
	return (arr);
}
