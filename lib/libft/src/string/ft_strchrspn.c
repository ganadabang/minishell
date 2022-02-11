/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:03:56 by gpaeng            #+#    #+#             */
<<<<<<< HEAD:lib/libft/src/string/ft_strlchr.c
/*   Updated: 2022/02/10 19:07:29 by gpaeng           ###   ########.fr       */
=======
/*   Updated: 2022/02/10 21:02:21 by hyeonsok         ###   ########.fr       */
>>>>>>> d0c4100a9a1f68d99e757a09b883160ad82f1c32:lib/libft/src/string/ft_strchrspn.c
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strchrspn(const char *str, int c) 
{
<<<<<<< HEAD:lib/libft/src/string/ft_strlchr.c
	int idx;

	idx = 0;
	if (!str)
		return(0);
	while (str[idx] && str[idx] != (char)c)
	{
		idx++;
=======
	size_t i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			break ;
		++i;
>>>>>>> d0c4100a9a1f68d99e757a09b883160ad82f1c32:lib/libft/src/string/ft_strchrspn.c
	}
	return (i);
}
