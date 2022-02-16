/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:34:22 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/17 05:41:37 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "mush/parser.h"

int	builtin_echo(t_state *state, int argc, char *argv[])
{
	t_buf	buffer;
	int		option_n;
	size_t	i;

	ft_memset(&buffer, 0, sizeof(t_buf));
	option_n = 0;
	i = 0;
	while (++i < argc)
	{
		if (ft_memcmp(argv[i], "-n", 2) == 0 \
			&& argv[i][1 + ft_strspn(&argv[i][1], "n")] == '\0')
			option_n = 1;
		else
		{
			hx_buffer_putstr(&buffer, argv[i], ft_strlen(argv[i]));
			break ;
		}
	}
	while (++i < argc)
	{
		if (argv[i] != NULL)
		{
			hx_buffer_putchar(&buffer, ' ');
			hx_buffer_putstr(&buffer, argv[i], ft_strlen(argv[i]));
		}	
	}
	if (option_n == 0)
		hx_buffer_putchar(&buffer, '\n');
	write(1, buffer.data, buffer.len);
	hx_buffer_cleanup(&buffer);
	return (0);
}
