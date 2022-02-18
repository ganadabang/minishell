/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:28:29 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/19 03:10:51 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "libft.h"
#include "mush.h"

static void	mush_print_env(t_array *envlist_ref)
{
	t_buf	buffer;
	char	**vars;
	size_t	len;
	size_t	i;

	ft_memset(&buffer, 0, sizeof(t_buf));
	vars = (char **)envlist_ref->data;
	len = envlist_ref->len;
	i = 0;
	while (i < len)
	{
		if (strchr(vars[i], '=') != NULL)
		{
			hx_buffer_putstr(&buffer, vars[i], strlen(vars[i]));
			hx_buffer_putchar(&buffer, '\n');
		}
		++i;
	}
	ft_puts(buffer.data);
	hx_buffer_cleanup(&buffer);
	return ;
}

int	builtin_env(t_state *state, int argc, char *argv[])
{
	(void)argv;
	if (argc > 1)
	{
		ft_dputendl(2, "env: too many arguments");
		return (1);
	}
	mush_print_env(&state->envlist);
	return (0);
}
