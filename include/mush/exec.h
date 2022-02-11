/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:56:20 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/11 16:55:37 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "mush.h"

int		is_last_proc(size_t idx, size_t size);
void	exec_pipe_connect(t_proc *proc);
void	exec_pipe_disconnect(int pde[2][2]);
void    exec_io_redirect(t_state *state_ref, t_array *io_files_ref);
void	mush_exec(t_job *job);
int		mush_execute(t_state *state);
int		mush_job_status_update(t_array *pipeline_ref);

size_t	exec_expn_buffer_putenv(t_state *state_ref, t_buf *buffer, char *word);
char	*exec_expn_word(t_state *state_ref, t_buf *buffer, char *word);
void	exec_expn_filename(t_state *state_ref, t_array *filenames_ref);
void	exec_expn_argv(t_state *state_ref, t_array *args_ref);

char	*exec_expn_cmd(t_state *state_ref, char *name);
void	mush_signal_retored();

#endif /* EXEC_H */
