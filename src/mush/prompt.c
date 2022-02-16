/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 17:18:07 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/16 23:42:58 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termios.h>
#include <signal.h>

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
	tcsetattr(STDOUT_FILENO, TCSANOW, term);
	return ;
}

void	mush_prompt_restored(struct termios *term)
{
	term->c_lflag |= ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, term);
	return ;
}
