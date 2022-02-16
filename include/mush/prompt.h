/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 17:17:43 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/16 23:44:57 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <termios.h>

void	mush_prompt_interactive(struct termios *term);
void	mush_prompt_blocked(struct termios *term);
void	mush_prompt_restored(struct termios *term);

#endif /* PROMPT_H */
