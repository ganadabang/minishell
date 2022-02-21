/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:56:00 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 17:00:49 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include "libfthx.h"
#include "mush/exec.h"

static int	exec_expn_filename(t_state *state, t_buf *buffer, t_file *file)
{
	char		*tofree;

	tofree = file->name;
	file->name = exec_expn_word(state, buffer, file->name);
	free(tofree);
	if (file->io_type == IO_IN)
		stat(file->name, NULL);
	if (file->name == NULL || file->name[0] == '\0' || errno == ENOENT)
		return (-1);
	return (0);
}

int	exec_proc_iofile_redirect(t_state *state, t_array *io_files_ref)
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
		if (files[i]->io_type != IO_HERE \
			&& exec_expn_filename(state, &buffer, files[i]) < 0)
			return (mush_error(files[i]->name, strerror(ENOENT)));
		fd = open(files[i]->name, files[i]->oflag, 0644);
		if (fd < 0)
			return (mush_error(files[i]->name, strerror(errno)));
		dup2(fd, files[i]->fd);
		close(fd);
		++i;
	}
	return (0);
}
