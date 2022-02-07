/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:56:00 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/07 12:38:45 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

void	exec_io_redirect(t_proc *proc)
{
	t_file	**io_files;
	int		fd;
	size_t	len;
	size_t	i;

	io_files = (t_file **)proc->io_files.data;
	len = proc->io_files.len;
	i = 0;
	while (i < len)
	{
		if (io_files[i]->io_type == IO_OUT || io_files[i]->io_type == IO_APPEND)
		{
			fd = open(io_files[i]->name, io_files[i]->oflag, 0644);
			//fatal error()
			if (fd < 0 || dup2(fd, 1) < 0)
				break ;
			close(fd);
		}
		else if (io_files[i]->io_type == IO_HERE || io_files[i]->io_type == IO_IN)
		{
			fd = open(io_files[i]->name, O_RDONLY, 0644);
			//fatal error()
			if (fd < 0 || dup2(fd, 0) < 0)
				break ;
			close(fd);
		}
		if (io_files[i]->io_type == IO_HERE)
			unlink("./.herdoc.tmp");
		++i;
	}
	return ;
}
