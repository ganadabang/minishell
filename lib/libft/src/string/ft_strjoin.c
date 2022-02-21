/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:55:48 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/21 13:42:44 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/string.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		ls1;
	int		ls2;
	char	*str;

	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (ls1 + ls2));
	if (!(str))
		return (0);
	ft_memcpy(str, s1, ls1);
	ft_memcpy(str + ls1, s2, ls2);
	str[ls1 + ls2] = '\0';
	return (str);
}

/*
** string join left free
*/
char	*ft_strjoin_lf(char *s1, const char *s2)
{
	char	*tofree;
	char	*str;

	tofree = s1;
	str = ft_strjoin(s1, s2);
	free(tofree);
	return (str);
}
