/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:56:20 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/25 14:31:26 by hyeonsok         ###   ########.fr       */
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
}	t_proc;

typedef struct s_job {
	t_array	pipeline;
	char	**envp;
	char	last_status;
	char	exit;
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
void	pipe_setup(int pde[2][2], int is_last_proc);
void	pipe_unset(int pde[2][2]);
void	io_redirect(t_file **io_files, size_t len);
void	mush_exec(t_job *job);

#endif
