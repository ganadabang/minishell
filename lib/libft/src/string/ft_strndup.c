/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:05:46 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/21 13:43:28 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/string.h"

char	*ft_strndup(char *str, size_t idx)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while (i < idx && str[i])
		i++;
	tmp = malloc(i + 1);
	if (tmp == NULL)
		return (NULL);
	ft_memcpy(tmp, str, i);
	tmp[i] = '\0';
	return (tmp);
}
