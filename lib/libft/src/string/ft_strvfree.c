/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strvfree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:37:26 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/17 01:59:15 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_strvfree(char **strv)
{
	int	i;

	i = 0;
	if (!strv)
		return ;
	while (strv[i])
		free(strv[i++]);
	free(strv);
	return ;
}
