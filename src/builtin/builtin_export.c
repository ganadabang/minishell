/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:53:12 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/23 16:26:59 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libfthx.h"
#include "mush/builtin.h"

static void	mush_export_print(t_state *state)
{
	t_buf	buffer;
	char	**envcpy;
	int		i;
	int		len;

	ft_memset(&buffer, 0, sizeof(buffer));
	len = state->envlist.len;
	envcpy = (char **)malloc((len + 1) * sizeof(char *));
	if (envcpy == NULL)
		mush_fatal("malloc");
	ft_memcpy(envcpy, state->envlist.data, (len + 1) * sizeof(char *));
	envcpy[len] = NULL;
	ft_strvsort(envcpy);
	i = 0;
	while (i < len)
	{
		hx_buffer_putstr(&buffer, envcpy[i], ft_strlen(envcpy[i]));
		hx_buffer_putchar(&buffer, '\n');
		++i;
	}
	free(envcpy);
	ft_puts(buffer.data);
	hx_buffer_cleanup(&buffer);
}

static void	mush_export_update(t_state *state, int argc, char *argv[], \
	int *result)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!mush_is_valid_name(argv[i]))
		{
			ft_dputs(2, "mush: export: `");
			ft_dputs(2, argv[i]);
			ft_dputs(2, "': not a valid identifier\n");
			*result = 1;
		}
		else
		{
			mush_put_env(state, argv[i]);
		}
		++i;
	}
	return ;
}

int	builtin_export(t_state *state, int argc, char *argv[])
{
	int	result;

	result = 0;
	if (argc == 1)
		mush_export_print(state);
	else if (argc >= 2)
		mush_export_update(state, argc, argv, &result);
	return (result);
}
