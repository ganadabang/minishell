/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:05:46 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/10 13:15:01 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

char *ft_strndup(char *str, int idx)
{
	char *tmp;
	size_t i;

	i = 0;
	if (!str)
		return (0);
	tmp = (char *)ft_set_malloc(sizeof(char), idx + 1);
	while (idx)
	{
		tmp[i] = str[i];
		i++;
		idx--;
	}
	tmp[i] = '\0';
	return tmp;
}