/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mush.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 17:25:14 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/04 19:59:40 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUSH_H
# define MUSH_H

#include "mush/parser.h"
#include "mush/builtin.h"
#include "mush/exec.h"
#include "mush/mode.h"

void	debug_pipeline(t_array *pipeline);

#endif
