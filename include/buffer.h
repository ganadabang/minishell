/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 12:46:44 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/23 22:01:48 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
#define BUFFER_H

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_buf {
	char	*data;
	size_t	len;
	size_t	cap;
}	t_buf;

bool	hx_buffer_secure(t_buf *buf, size_t size);
bool	hx_buffer_putstr(t_buf *buf, const char *data, size_t size);
bool	hx_buffer_putchar(t_buf *buf, char c);
char	*hx_buffer_withdraw(t_buf *buf);
void	hx_buffer_cleanup(t_buf *buf);

#endif