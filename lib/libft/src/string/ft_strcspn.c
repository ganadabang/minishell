/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 17:48:28 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 03:25:43 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

size_t	ft_strcspn(const char *s, const char *charset)
{
	char	*p;

	p = (char *)s;
	while (*p)
	{
		if (ft_strchr(charset, *p))
			break ;
		p++;
	}
	return (p - s);
}
