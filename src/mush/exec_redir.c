/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:56:00 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 11:20:47 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include "libft.h"
#include "mush/exec.h"

#include <stdio.h>

static void	exec_expn_filename(t_state *state_ref, t_buf *buffer, t_file *file)
{
	char		*tofree;

	tofree = file->name;
	file->name = exec_expn_word(state_ref, buffer, file->name);
	free(tofree);
	return ;
}

int	exec_proc_iofile_redirect(t_state *state_ref, t_array *io_files_ref)
{
	t_buf	buffer;
	t_file	**files;
	int		fd;
	size_t	i;

	files = (t_file **)io_files_ref->data;
	if (files == NULL)
		return (0);
	ft_memset(&buffer, 0, sizeof(t_buf));
	i = 0;
	while (files[i] != NULL)
	{
		if (files[i]->io_type != IO_HERE)
			exec_expn_filename(state_ref, &buffer, files[i]);
		fd = open(files[i]->name, files[i]->oflag, 0644);
		if (fd < 0)
		{
			mush_error(files[i]->name, strerror(errno));
			return (-1);
		}
		dup2(fd, files[i]->fd);
		close(fd);
		++i;
	}
	return (0);
}
