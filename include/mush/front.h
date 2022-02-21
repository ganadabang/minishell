/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   front.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 03:01:39 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 17:42:43 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRONT_H
# define FRONT_H

# include <termios.h>

void	mush_prompt_interactive(struct termios *term);
void	mush_prompt_blocked(struct termios *term);
void	mush_prompt_restored(struct termios *term);

void	mush_signal_set(void);
void	mush_signal_restored(void);

#endif /* FRONT_H */
