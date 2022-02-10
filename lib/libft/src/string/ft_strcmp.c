/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:07:04 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/10 21:46:43 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int		ft_strcmp(const char *str1, const char *str2)
{
	size_t i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		++i;
	return (str1[i] - str2[i]);
}