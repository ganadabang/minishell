/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:34:22 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/21 16:56:40 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libfthx.h"
#include "mush/builtin.h"

static int	echo_check_option_n(int argc, char *argv[], t_buf *buffer, \
	int *idx_ref)
{
	int	i;
	int	option_n;

	i = 0;
	option_n = 0;
	while (++i < argc)
	{
		if (ft_memcmp(argv[i], "-n", 2) == 0 \
			&& argv[i][1 + ft_strspn(&argv[i][1], "n")] == '\0')
			option_n = 1;
		else
		{
			hx_buffer_putstr(buffer, argv[i], ft_strlen(argv[i]));
			break ;
		}
	}
	*idx_ref = i;
	return (option_n);
}

static void	echo_print_args(int argc, char *argv[], t_buf *buffer, int *idx_ref)
{
	int	i;

	i = *idx_ref;
	while (++i < argc)
	{
		if (argv[i] != NULL)
		{
			hx_buffer_putchar(buffer, ' ');
			hx_buffer_putstr(buffer, argv[i], ft_strlen(argv[i]));
		}	
	}
	*idx_ref = i;
	return ;
}

int	builtin_echo(t_state *state, int argc, char *argv[])
{
	t_buf	buffer;
	int		option_n;
	int		i;

	(void)state;
	ft_memset(&buffer, 0, sizeof(t_buf));
	option_n = echo_check_option_n(argc, argv, &buffer, &i);
	echo_print_args(argc, argv, &buffer, &i);
	if (option_n == 0)
		hx_buffer_putchar(&buffer, '\n');
	write(1, buffer.data, buffer.len);
	hx_buffer_cleanup(&buffer);
	return (0);
}
