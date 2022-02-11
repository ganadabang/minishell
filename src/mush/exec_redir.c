/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:56:00 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/11 21:56:18 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "mush/parser.h"
#include "mush/exec.h"

void	exec_io_redirect(t_state *state_ref, t_array *io_files_ref)
{
	t_buf	buffer = {};
	t_file	*file;
	int		fd;
	size_t	len;
	size_t	i;
	

	len = io_files_ref->len;
	i = 0;
	while (i < len)
	{
		file = (t_file *)io_files_ref->data[i];
		file->name = exec_expn_word(state_ref, &buffer, file->name);
		if (file->io_type == IO_OUT || file->io_type == IO_APPEND)
		{
			fd = open(file->name, file->oflag, 0644);
			if (fd < 0 || dup2(fd, 1) < 0)
				break ;
			close(fd);
		}
		else if (file->io_type == IO_HERE || file->io_type == IO_IN)
		{
			fd = open(file->name, O_RDONLY, 0644);
			if (fd < 0)
				mush_fatal("open");
			if (dup2(fd, 0) < 0)
				mush_fatal("dup2");
			close(fd);
		}
		++i;
	}
	return ;
}
