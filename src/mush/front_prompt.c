/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   front_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 17:18:07 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 14:26:19 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "libft.h"
#include "mush.h"
#include "mush/front.h"
#include "mush/exec.h"

static void	sig_handler_sigchld(int signum)
{
	t_state	*state;

	if (signum != SIGCHLD)
		return ;
	state = g_state;
	state->job.status = mush_poll_status(&state->job.pipeline);
	free(state->last_status);
	state->last_status = ft_itoa(state->job.status);
	if (state->last_status == NULL)
		mush_fatal("malloc");
	mush_cleanup_pipeline(&state->job.pipeline);
}

void	mush_prompt_interactive(struct termios *term)
{
	term->c_lflag &= ~ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, term);
	return ;
}

void	mush_prompt_blocked(struct termios *term)
{
	term->c_lflag |= ECHOCTL;
	signal(SIGINT, SIG_IGN);
	signal(SIGCHLD, sig_handler_sigchld);
	tcsetattr(STDOUT_FILENO, TCSANOW, term);
	return ;
}

void	mush_prompt_restored(struct termios *term)
{
	term->c_lflag |= ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, term);
	return ;
}
