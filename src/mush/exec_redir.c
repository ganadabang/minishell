/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:56:00 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/15 20:10:05 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"
#include "mush/parser.h"
#include "mush/exec.h"

void	exec_io_redirect(t_state *state_ref, t_array *io_files_ref)
{
	t_buf	buffer;
	t_file	*file;
	t_file	**files;
	char	*tofree;
	int		fd;
	size_t	i;
	
	ft_memset(&buffer, 0, sizeof(t_buf));
	files = (t_file **)io_files_ref->data;
	if (files == NULL)
		return ;
	i = 0;
	while (files[i] != NULL)
	{
		file = files[i];
		if (file->io_type != IO_HERE)
		{
			tofree = file->name;
			file->name = exec_expn_word(state_ref, &buffer, file->name);
			free(tofree);
		}
		fd = open(file->name, file->oflag, 0644);
		if (fd < 0)
			mush_fatal("open");
		if (dup2(fd, file->fd) < 0)
			mush_fatal("dup2");
		close(fd);
		++i;
	}
	return ;
}
