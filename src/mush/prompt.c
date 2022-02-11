/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 02:54:41 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/11 15:09:06 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include <readline/readline.h>

static void	sig_handler_int(int signum)
{
	if (signum & SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

static void	sig_handler_winch(int signum)
{
	if (signum & SIGWINCH)
		rl_on_new_line();
	return ;
}

void	mush_prompt_interactive(struct termios *term)
{
	term->c_lflag &= ~ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW ,term);
}

void	mush_prompt_executive(struct termios *term)
{
	term->c_lflag |= ECHOCTL;
	signal(SIGINT, SIG_IGN);
	tcsetattr(STDOUT_FILENO, TCSANOW ,term);
}

void	mush_prompt_signal(void)
{
	signal(SIGWINCH, sig_handler_winch);
	signal(SIGINT, sig_handler_int);
	signal(SIGCHLD, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGCONT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	return ;
}

void	mush_prompt_restored(struct termios *term)
{
	term->c_lflag |= ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW ,term);
}
