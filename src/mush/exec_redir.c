/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:56:00 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 03:19:16 by hyeonsok         ###   ########.fr       */
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

int	exec_proc_io_redirect(t_state *state_ref, t_array *io_files_ref)
{
	t_buf	buffer;
	t_file	**files;
	char	*tofree;
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
		{
			tofree = files[i]->name;
			files[i]->name = exec_expn_word(state_ref, &buffer, files[i]->name);
			free(tofree);
			stat(files[i]->name, NULL);
			if (errno == ENOENT || errno == EFAULT)
				return (mush_error(files[i++]->name, strerror(ENOENT)));
		}
		fd = open(files[i]->name, files[i]->oflag, 0644);
		if (fd < 0)
			mush_fatal("open");
		if (dup2(fd, files[i]->fd) < 0)
			mush_fatal("dup2");
		close(fd);
		++i;
	}
	return (0);
}
