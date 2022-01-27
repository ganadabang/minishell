/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:56:20 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/27 12:22:19 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <stdio.h>
# include <stdio.h>

# include "libftx.h"

typedef struct s_proc {
	char *name;
	char **argv;
	t_array	io_redirect;
	pid_t	pid;
	int		status;
	int		iscompleted;
}	t_proc;

typedef struct s_job {
	t_array	pipeline;
	char	**envp;
	int		last_status;
}	t_job;

typedef struct s_file {
	char	*name;
	int		io_type;
}	t_file;

enum	e_iotype {
	IO_IN,
	IO_OUT,
	IO_APPEND,
	IO_HERE
};

int		is_last_proc(size_t idx, size_t size);
void	exec_pipe_connect(int pde[2][2]);
void	exec_pipe_disconnect(int pde[2][2]);
void	io_redirect(t_file **io_files, size_t len);
void	mush_exec(t_job *job);
int		exec_state_update(t_proc *procs[], size_t len);

#endif
