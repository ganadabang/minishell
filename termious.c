/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termious.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 21:01:28 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/10/28 21:46:24 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <termios.h>

/*
tcsetattr, tcgetattr,

termcap
tgetent, tgetflag, tgetnum, tgetstr, tgoto,tputs
*/
int main(void)
{
	typedef struct termios t_termios;
	t_termios *ttyset;
	tcgetattr(0, ttyset);
	tcgetattr(1, ttyset);
	return (0);
}