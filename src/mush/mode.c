/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 02:54:41 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/01 12:56:34 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <signal.h>
#include <readline/readline.h>

void	mush_sighandler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGWINCH)
		rl_on_new_line();
	return ;
}

void	mush_mode_interactive(struct termios *term)
{
	signal(SIGINT, mush_sighandler);
	term->c_lflag &= ~ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW ,term);
}

void	mush_mode_executive(struct termios *term)
{
	signal(SIGINT, SIG_IGN);
	term->c_lflag |= ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW ,term);
}

void	mush_signal(void)
{
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGWINCH, mush_sighandler);
	return ;
}

void	mush_term_restored(struct termios *term)
{
	term->c_lflag |= ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW ,term);
}
