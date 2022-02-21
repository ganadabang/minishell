/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:56:20 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 17:48:42 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "mush.h"

int		builtin_search(t_proc *proc);
void	mush_exec_builtin(t_state *state_ref);

void	mush_cleanup_pipeline(t_array *pipeline);

char	*exec_expn_cmd(t_state *state_ref, char *name);

char	*exec_expn_word(t_state *state_ref, t_buf *buffer, char *word);
void	exec_expn_argv(t_state *state_ref, t_array *exec_argv);

int		mush_poll_status(t_array	*pipeline);

int		exec_proc_iofile_redirect(t_state *state, t_array *io_files_ref);

void	mush_execute(t_state *state);

#endif /* EXEC_H */
