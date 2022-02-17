/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:28:29 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/17 14:10:02 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "libft.h"
#include "mush.h"

int	builtin_env(t_state *state, int argc, char *argv[])
{
	t_buf	buffer;
	char	**env;
	char	*str;
	size_t	i;

	if (argc > 1)
	{
		ft_dputendl(2, "env: too many arguments");
		return (1);
	}
	ft_memset(&buffer, 0, sizeof(t_buf));
	env = state->envp;
	i = 0;
	while (env[i] != NULL)
	{
		hx_buffer_putstr(&buffer, env[i], ft_strlen(env[i]));
		hx_buffer_putchar(&buffer, '\n');
		++i;
	}
	ft_puts(buffer.data);
	hx_buffer_cleanup(&buffer);
	return (0);
}
