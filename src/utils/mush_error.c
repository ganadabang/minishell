/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mush_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:12:54 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 16:31:35 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libfthx.h"
#include "mush.h"

void	mush_fatal(const char *fn_name)
{
	perror(fn_name);
	exit(1);
}

int	mush_error(const char *str, const char *strerr)
{
	t_buf	buffer;

	ft_memset(&buffer, 0, sizeof(buffer));
	hx_buffer_putstr(&buffer, "mush: ", 6);
	hx_buffer_putstr(&buffer, str, ft_strlen(str));
	hx_buffer_putstr(&buffer, ": ", 2);
	hx_buffer_putstr(&buffer, strerr, ft_strlen(strerr));
	hx_buffer_putchar(&buffer, '\n');
	write(2, buffer.data, buffer.len);
	free(buffer.data);
	return (-1);
}
