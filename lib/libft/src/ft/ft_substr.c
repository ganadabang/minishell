/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 17:30:56 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/10 21:53:38 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_substr(char const *s1, unsigned int start, size_t len)
{
	char	*s;
	char	*iter;

	s = (char *)malloc((len + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	s1 += start;
	iter = s;
	while (len > 0)
	{
		*iter++ = *s1++;
		--len;
	}
	*iter = '\0';
	return (s);
}
