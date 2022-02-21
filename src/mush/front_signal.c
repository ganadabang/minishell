/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   front_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 02:54:41 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 17:05:18 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include "mush/front.h"

static void	sig_handler_winch(int signum)
{
	if (signum == SIGWINCH)
		rl_on_new_line();
	return ;
}

void	mush_signal_restored(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	return ;
}

void	mush_signal_set(void)
{
	signal(SIGWINCH, sig_handler_winch);
	signal(SIGCHLD, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGCONT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	return ;
}
