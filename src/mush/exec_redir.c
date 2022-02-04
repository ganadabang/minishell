/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:56:00 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/04 17:31:06 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

void	io_redirect(t_file **io_files, size_t len)
{
		
	for (size_t i = 0; i < len; ++i)
	{
		if (io_files[i]->io_type == IO_OUT)
		{
			int	fd = open(io_files[i]->name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			dup2(fd, 1);
			close(fd);
		}
		else if (io_files[i]->io_type == IO_IN)
		{
			int	fd = open(io_files[i]->name, O_RDONLY, 0644);
			dup2(fd, 0);
			close(fd);
		}
		else if (io_files[i]->io_type == IO_APPEND)
		{
			int	fd = open(io_files[i]->name, O_CREAT | O_WRONLY | O_APPEND , 0644);
			dup2(fd, 1);
			close(fd);
		}
		else if (io_files[i]->io_type == IO_HERE)
		{
			int	fd = open(io_files[i]->name, O_RDONLY, 0644);
			dup2(fd, 0);
			close(fd);
		}
	}
}
