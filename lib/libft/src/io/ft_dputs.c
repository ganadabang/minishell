/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 21:24:44 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/10 18:07:53 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft/string.h"

int	ft_dputs(int fd, const char *s)
{
	return (write(fd, s, ft_strlen(s)));
}
