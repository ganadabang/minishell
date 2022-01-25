/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_io.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 21:00:58 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/11/05 01:13:51 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  __FT_IO__H__
# define __FT_IO__H__

#include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX _SC_OPEN_MAX
# endif

/*
 * stdout
 */
int	ft_putc(int c);
int	ft_puts(const char *s);
int	ft_putendl(const char *s);
int	ft_putnbr(int n);
/*
 * with fd
 */
int	ft_dputc(int fd, int c);
int	ft_dputs(int fd, const char *s);
int	ft_dputendl(int fd, const char *s);
int	ft_dputnbr(int fd, int n);

int get_next_line(int fd, char **lineptr);
int ft_printf(const char *format, ...);

#endif  //FT_IO_H
