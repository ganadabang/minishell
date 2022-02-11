/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 18:22:07 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/10 21:49:42 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/string.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	char	*iter;

	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new == NULL)
	{
		return (NULL);
	}
	iter = new;
	while (*s1 != '\0')
	{
		*iter = *s1;
		++iter;
		++s1;
	}
	while (*s2 != '\0')
	{
		*iter = *s2;
		++iter;
		++s1;
	}
	*iter = '\0';
	return (new);
}
