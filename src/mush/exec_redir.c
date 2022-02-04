/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:56:00 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/04 19:41:13 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

void	mush_io_redirect(t_proc *proc)
{
	t_file	**io_files;
	int		fd;
	size_t	len;
	size_t	i;

	io_files = (t_file **)proc->io_files.data;
	len = proc->io_files.len;
	i = -1;
	while (++i < len)
	{
		if (io_files[i]->io_type == IO_OUT)
		{
			close(proc->stdout);
			fd = open(io_files[i]->name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (fd < 0 || dup2(fd, 1) < 0)
				break ;
			close(fd);
		}
		else if (io_files[i]->io_type == IO_IN)
		{
			fd = open(io_files[i]->name, O_RDONLY, 0644);
			if (fd < 0 || dup2(fd, 0) < 0)
				break ;
			close(fd);
		}
		else if (io_files[i]->io_type == IO_APPEND)
		{
			fd = open(io_files[i]->name, O_CREAT | O_WRONLY | O_APPEND , 0644);
			if (fd < 0 || dup2(fd, 1) < 0)
				break ;
			close(fd);
		}
		else if (io_files[i]->io_type == IO_HERE)
		{
			fd = open("./.heredoc.tmp", O_RDONLY, 0644);
			if (fd < 0 || dup2(fd, 0))
				break ;
			close(fd);
			unlink("./.herdoc.tmp");
		}
	}
	return ;
}
