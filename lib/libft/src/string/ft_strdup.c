/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 17:44:28 by SSONG             #+#    #+#             */
/*   Updated: 2022/02/10 20:58:51 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/string.h"

char	*ft_strdup(const char *s1)
{
	char	*s;
	char	*iter;

	s = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	iter = s;
	while (*s1 != '\0')
	{
		*iter = *s1;
		++iter;
		++s1;
	}
	*iter = '\0';
	return (s);
}
