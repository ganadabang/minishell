/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort_envp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:52:33 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/11 17:30:38 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mush/builtin.h"

//To be removed
#include <string.h>

int	bubble_sort_envp(char **str)
{
	int	i;
	int	j;
	int	n;
	int m;

	j = ft_cnt_arg(str);
	while (--j)
	{
		i = 0;
		while (i < j)
		{
			n = strcspn(str[i], "=");
			m = strcspn(str[i + 1], "=");
			if (n < m)
				n = m;
			if (ft_memcmp(str[i], str[i + 1], n) > 0)
				ft_strswap(&str[i], &str[i+1]);
			i++;
		}
	}
	return (0);
}
