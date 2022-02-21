/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 17:48:47 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 13:43:47 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

char	*ft_strtok(const char *str, const char *sep)
{
	static char	*save;
	char		*tok;
	char		*brk;

	if (str)
		save = (char *)str;
	if (!save)
		return (NULL);
	tok = save + ft_strspn(save, sep);
	if (!*tok)
	{
		save = NULL;
		return (NULL);
	}
	brk = ft_strpbrk(tok, sep);
	if (brk)
	{
		*brk = '\0';
		save = ++brk;
	}
	else
		save = NULL;
	return (tok);
}
