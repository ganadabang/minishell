/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:24:06 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/15 20:57:20 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_add_path(char **path_v, char *slash)
{
	char	*tmp;

	tmp = ft_strjoin(*path_v, slash);
	free(*path_v);
	*path_v = tmp;
}
