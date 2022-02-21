/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:47:55 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 14:29:11 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "mush/front.h"
#include "mush/parser.h"
#include "mush/exec.h"

static void	mush_init(t_state *state_ref, char **envp)
{
	size_t	i;

	ft_memset(state_ref, 0, sizeof(t_state));
	tcgetattr(STDOUT_FILENO, &state_ref->term);
	i = 0;
	while (envp[i] != NULL)
	{
		hx_array_push(&state_ref->envlist, ft_strdup(envp[i]));
		++i;
	}
	state_ref->exit = -1;
	state_ref->last_status = ft_itoa(0);
	if (state_ref->last_status == NULL)
		mush_fatal("malloc");
	return ;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_state	state;

	(void)argv;
	if (argc != 1)
		return (1);
	mush_init(&state, envp);
	g_state = &state;
	mush_signal_set();
	while (state.exit == -1)
	{
		mush_prompt_interactive(&state.term);
		if (mush_parser_readline(&state) < 0)
			continue ;
		mush_prompt_blocked(&state.term);
		mush_execute(&state);
	}
	mush_prompt_restored(&state.term);
	printf("exit\n");
	return (0);
}
