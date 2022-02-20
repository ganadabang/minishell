/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_iofile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 02:02:14 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/20 19:42:13 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include "libfthx.h"
#include "mush.h"

static void	infile_init(t_file *file, char *redir_op)
{
	file->fd = STDIN_FILENO;
	file->oflag = O_RDONLY;
	if (ft_memcmp("<", redir_op, 2) == 0)
	{
		file->io_type = IO_IN;
		return ;
	}
	file->io_type = IO_HERE;
	return ;
}

static void	outfile_init(t_file *file, char *redir_op)
{
	file->fd = STDOUT_FILENO;
	if (ft_memcmp(">", redir_op, 2) == 0)
	{
		file->io_type = IO_OUT;
		file->oflag = O_CREAT | O_TRUNC | O_WRONLY;
		return ;
	}
	file->io_type = IO_APPEND;
	file->oflag = O_CREAT | O_APPEND | O_WRONLY;
	return ;
}

static char	*here_remove_quoting(char *word)
{
	t_buf	buffer;
	char	*here_end;
	size_t	i;

	i = 0;
	ft_memset(&buffer, 0, sizeof(buffer));
	while (word[i] != '\0')
	{
		if (word[i] != '\'' && word[i] != '"')
			hx_buffer_putchar(&buffer, word[i]);
		++i;
	}
	here_end = hx_buffer_withdraw(&buffer);
	if (here_end == NULL)
		here_end = ft_strdup("");
	return (here_end);
}

static void	heredoc_init(t_file *file)
{
	char	*input;
	char	*here_end;
	size_t	here_len;
	int		fd;

	here_end = here_remove_quoting(file->name);
	free(file->name);
	file->name = "./.here_tmp";
	here_len = 1 + ft_strlen(here_end);
	fd = open("./.here_tmp", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		mush_fatal("open");
	while (1)
	{
		input = readline("heredoc> ");
		if (input == NULL || ft_memcmp(here_end, input, here_len) == 0)
			break ;
		ft_dputendl(fd, input);
		free(input);
	}
	free(here_end);
	free(input);
	close(fd);
	return ;
}

t_file	*parser_create_io_file(char **redir_ref, char *str)
{
	t_file	*file;
	char	*redir_op;

	redir_op = *redir_ref;
	file = (t_file *)ft_calloc(1, sizeof(t_file));
	if (file == NULL)
		mush_fatal("malloc");
	if ('<' == *redir_op)
		infile_init(file, redir_op);
	else if ('>' == *redir_op)
		outfile_init(file, redir_op);
	free(redir_op);
	*redir_ref = NULL;
	file->name = str;
	if (file->io_type == IO_HERE)
		heredoc_init(file);
	return (file);
}
