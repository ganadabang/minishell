/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:31:28 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/24 21:18:03 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>


void	io_redirect(t_file **io_files, size_t len)
{
		
	for (int i = 0; i < len; ++i)
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
			int	fd = open(io_files[i]->name, O_CREAT | O_TRUNC | O_WRONLY | O_APPEND , 0644);
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

int	is_last_proc(size_t idx, size_t size)
{
	return (++idx == size);
}

void	pipe_setup(int pde[2][2], int is_last_proc)
{
	if (!is_last_proc)
	{
		dup2(pde[0][1], 1);
		close(pde[0][1]);
	}
	if (pde[1][0] != -1)
	{
		dup2(pde[1][0], 0);
		close(pde[1][0]);
	}
}

void	pipe_unset(int pde[2][2])
{
	close(pde[0][1]);
	close(pde[1][0]);
	memcpy(pde[1],pde[0], 2 * sizeof(int));
}

int	main(int argc, char **argv, char **envp)
{
	t_job		job = (t_job){{0}, envp, 0, 0};
	t_file		io_file = {"outfile", IO_OUT};
	t_proc		proc1 = {"/bin/ls", (char *[]){"/bin/ls", "-l", NULL}, 0};
	t_proc		proc2 = {"/usr/bin/grep", (char *[]){"usr/bin/grep", "a.out", NULL}, 0};
	int			pde[2][2] = {{-1, -1}, {-1, -1}};
	pid_t		pid;

	//lexer
	//parser
	hx_array_push(&proc1.io_redirect, &io_file);
	hx_array_push(&job.pipeline, &proc1);
	hx_array_push(&job.pipeline, &proc2);

	//executor
	for (int i = 0; i < job.pipeline.len; ++i)
	{
		pipe(pde[0]);
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		t_proc *command = job.pipeline.data[i];
		if (pid == 0)
		{
			pipe_setup(pde, is_last_proc(i, job.pipeline.len));
			io_redirect((t_file **)command->io_redirect.data, command->io_redirect.len);
			//command_expansioin
			//filename_expansion
			execve(command->name, command->argv, job.envp);
			puts("Error");
		}
		pipe_unset(pde);
	}
	close(pde[1][0]);
	//sync exit state
	return (0);
}
