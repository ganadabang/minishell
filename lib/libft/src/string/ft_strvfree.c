/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strvfree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:37:26 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/21 03:26:25 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/string.h"

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
