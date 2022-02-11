/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 17:48:56 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/11 17:50:40 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

char	*ft_strpbrk(const char *s, const char *charset)
{
	char	*p;

	p = (char *)s;
	while (*p)
	{
		if (ft_strchr(charset, *p))
			return (p);
		p++;
	}
	return (NULL);
}
