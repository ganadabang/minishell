/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:15:48 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/23 22:01:39 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "buffer.h"

bool	hx_buffer_secure(t_buf *buf, size_t size)
{
	size_t	new_len;
	size_t	new_cap;

	new_len = buf->len + size;
	if (buf->cap >= new_len)
		return (true);
	new_cap = 2 * buf->cap;
	if (new_cap == 0)
		new_cap = 32;
	if (new_cap < new_len)
		new_cap = new_len;
	buf->data = (char *)realloc(buf->data, new_cap);
	if (!buf->data)
		return (false);
	buf->cap = new_cap;
	return (true);
}

bool	hx_buffer_putstr(t_buf *buf, const char *data, size_t size)
{
	if (!hx_buffer_secure(buf, size))
		return (false);
	memcpy(&buf->data[buf->len], data, size);
	buf->len += size;
	return (true);
}

bool	hx_buffer_putchar(t_buf *buf, char c)
{
	if (!hx_buffer_secure(buf, sizeof(char)))
		return (false);
	buf->data[buf->len] = c;
	buf->len += 1;
	return (true);
}

char	*hx_buffer_withdraw(t_buf *buf)
{
	char	*data;

	data = buf->data;
	buf->data = NULL;
	buf->len = 0;
	return (data);
}

void	hx_buffer_cleanup(t_buf *buf)
{
	free(buf->data);
	buf->data = NULL;
	buf->cap = 0;
	buf->len = 0;
}