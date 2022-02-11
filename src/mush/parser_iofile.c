/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_iofile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 02:02:14 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/11 21:51:30 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include "libfthx.h"
#include "mush.h"

static int	get_type(char *str)
{
	if (ft_memcmp("<<", str, 3) == 0)
		return (IO_HERE);
	if (ft_memcmp(">>", str, 3) == 0)
		return (IO_APPEND);
	if (ft_memcmp("<", str, 2) == 0)
		return (IO_IN);
	if (ft_memcmp(">", str, 2) == 0)
		return (IO_OUT);
	return (-1);
}

static int	get_oflag(int io_type)
{
	if (io_type & IO_HERE || io_type & IO_IN)
		return (O_RDONLY);
	if (io_type == IO_OUT)
		return (O_CREAT | O_TRUNC | O_WRONLY);
	if (io_type == IO_APPEND)
		return (O_CREAT | O_APPEND | O_WRONLY);
	return (-1);
}

static char	*remove_quoting(char *here_end)
{
	t_buf	buffer;
	char	*ret;

	ft_memset(&buffer, 0, sizeof(buffer));
	while (here_end)
	{
		if (*here_end != '\'' && *here_end != '"')
			hx_buffer_putchar(&buffer, *here_end);
		++here_end;
	}
	ret = hx_buffer_withdraw(&buffer);
	return (ret);
}

t_file	*parser_create_io_file(char *redir, char *str)
{
	t_file	*file;
	char	*here_end;
	char	*input;
	size_t	here_len;
	int		fd;

	file = (t_file *)ft_calloc(1, sizeof(t_file));
	if (file == NULL)
		mush_fatal("malloc");
	file->io_type = get_type(redir);
	file->oflag = get_oflag(file->io_type);
	file->name = str;
	if (file->io_type == IO_HERE)
	{
		here_end = remove_quoting(str);
		free(str);
		here_len = ft_strlen(here_end);
		file->name = "./.here_tmp";
		fd = open(file->name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		free(here_end);
		if (fd < 0)
			mush_fatal("open");
		while (1)
		{
			input = readline(">");
			if (ft_memcmp(here_end, input, here_len) == 0)
				break ;
			ft_dputendl(fd, input);
		}
		close(fd);
	}
	return (file);
}