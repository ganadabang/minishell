/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:56:20 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/04 19:57:55 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <stdio.h>
# include <stdio.h>

# include "libftx.h"

int		is_last_proc(size_t idx, size_t size);
void	exec_pipe_connect(int pde[2][2]);
void	exec_pipe_disconnect(int pde[2][2]);
void	mush_io_redirect(t_proc *proc);
void	mush_exec(t_job *job);
int		mush_execute(t_state *state);
int		mush_job_status_update(t_job *job);

#endif
