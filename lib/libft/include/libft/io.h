/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 21:00:58 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/10 18:51:52 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  IO_H
# define IO_H

int	ft_putchar(int c);
int	ft_puts(const char *s);
int	ft_putendl(const char *s);
int	ft_putnbr(int n);
int	ft_dputchar(int fd, int c);
int	ft_dputs(int fd, const char *s);
int	ft_dputendl(int fd, const char *s);
int	ft_dputnbr(int fd, int n);

#endif /* IO_H */
