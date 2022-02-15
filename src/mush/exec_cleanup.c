/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 19:24:30 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/15 20:02:01 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libfthx.h"
#include "mush/exec.h"

static void	cleanup_argv(t_array *exec_argv)
{
	char	**data;
	size_t	len;
	size_t	i;

	data = (char **)exec_argv->data;
	len = exec_argv->len;
	i = 0;
	while (i < len)
		free(data[i++]);
	free(data);
	data = NULL;
}

static void	cleanup_io_files(t_array *io_files)
{
	t_file	**data;
	size_t	len;
	size_t	i;

	data = (t_file **)io_files->data;
	if (data == NULL)
		return ;
	len = io_files->len;
	i = 0;
	while (i < len)
	{
		if (data[i]->io_type == IO_HERE)
		{
			unlink("./here_tmp");
			data[i]->name = NULL;
		}
		free(data[i]->name);
		free(data[i++]);
	}
	free(data);
	data = NULL;
}

void	mush_cleanup_pipeline(t_array *pipeline)
{
	t_proc	**procs;
	size_t	len;
	size_t	i;

	procs = (t_proc **)pipeline->data;
	len = pipeline->len;
	i = 0;
	while (i < len)
	{
		// free(procs[i]->name);
		cleanup_argv(&procs[i]->argv);
		cleanup_io_files(&procs[i]->io_files);
		free(procs[i++]);
	}
	hx_array_cleanup(pipeline);
	return ;
}
