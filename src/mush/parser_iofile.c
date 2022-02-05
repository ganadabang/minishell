/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_iofile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 02:02:14 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/05 02:06:02 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

// TODO strcmp -> ft_strcmp
static int	get_io_type(char *str)
{
	if (strcmp("<<", str) == 0)
		return (IO_HERE);
	if (strcmp(">>", str) == 0)
		return (IO_APPEND);
	if (strcmp("<", str) == 0)
		return (IO_IN);
	if (strcmp(">", str) == 0)
		return (IO_OUT);
	return (-1);
}

static int	get_oflag(int io_type)
{
	if (io_type == IO_HERE || io_type == IO_IN)
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
	hx_buffer_cleanup(&buffer);
	return (ret);
}

t_file	*parser_create_io_file(char *redir, char *str)
{
	t_file	*file;
	char	*here_end;
	char	*input;
	int		fd;

	file = (t_file *)calloc(1, sizeof(t_file));
	file->io_type = get_io_type(redir);
	file->oflag = get_oflag(file->io_type);
	file->name = str;
	if (file->io_type == IO_HERE)
	{

		here_end = remove_quoting(str);
		file->name = "./.here_tmp";
		fd = open(file->name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		while (1)
		{
			input = readline(">");
			if (strcmp(here_end, input) == 0)
				break ;
			ft_dputendl(fd, input);
		}
		close(fd);
	}
	return (file);
}