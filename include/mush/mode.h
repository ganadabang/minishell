/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 03:01:39 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/30 03:02:57 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_H
# define MODE_H

#include <termios.h>

void	mush_mode_interactive(struct termios *term);
void	mush_mode_executive(struct termios *term);
void	mush_signal(void);
void	mush_term_restored(struct termios *term);
void	mush_sighandler(int signum);

#endif
