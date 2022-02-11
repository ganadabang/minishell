/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 03:01:39 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/11 16:05:02 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <termios.h>

void	mush_prompt_signal(void);
void	mush_prompt_interactive(struct termios *term);
void	mush_prompt_executive(struct termios *term);
void	mush_prompt_restored(struct termios *term);

#endif /* PROMPT_H */
