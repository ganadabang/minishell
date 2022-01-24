/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:10:05 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/24 21:17:52 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define  EXEC_H

#include "array.h"

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
	int		here_fd;
}	t_file;

enum	e_iotype {
	IO_IN,
	IO_OUT,
	IO_APPEND,
	IO_HERE
};

#endif
