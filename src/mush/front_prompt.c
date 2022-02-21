/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   front_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 17:18:07 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 15:44:20 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "libft.h"
#include "mush/front.h"
#include "mush/exec.h"

static void	sig_handler_int(int signum)
{
	if (signum != SIGINT)
		return ;
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

void	mush_prompt_interactive(struct termios *term)
{
	term->c_lflag &= ~ECHOCTL;
	signal(SIGINT, sig_handler_int);
	signal(SIGCHLD, SIG_IGN);
	tcsetattr(STDOUT_FILENO, TCSANOW, term);
	return ;
}

void	mush_prompt_blocked(struct termios *term)
{
	term->c_lflag |= ECHOCTL;
	signal(SIGINT, SIG_IGN);
	tcsetattr(STDOUT_FILENO, TCSANOW, term);
	return ;
}

void	mush_prompt_restored(struct termios *term)
{
	term->c_lflag |= ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, term);
	return ;
}
