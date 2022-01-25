/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 20:19:50 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/25 01:23:37 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"

static char	*check_save(char **save)
{
	if (!*save)
	{
		*save = ft_strdup("");
		if (!*save)
			return (NULL);
	}
	return (*save);
}

static int	clean_save(char **save)
{
	if (!*save)
		return (-1);
	free(*save);
	*save = NULL;
	return (-1);
}

static int	real_cat(char **save, char buff[], size_t size)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strdup(*save);
	free(*save);
	*save = NULL;
	*save = (char *)malloc(sizeof(char) * size);
	if (!tmp || !*save)
	{
		free(*save);
		*save = NULL;
		free(tmp);
		return (0);
	}
	ft_memcpy(*save, tmp, ft_strlen(tmp) + 1);
	free(tmp);
	ft_strlcat(*save, buff, size);
	return (1);
}

static int	takeout_line(char **lineptr, char **save, char *newline)
{
	char	*tmp;

	tmp = NULL;
	if (newline != NULL)
	{
		*newline = '\0';
		*lineptr = ft_strdup(*save);
		tmp = ft_strdup(++newline);
		if (!*lineptr || !tmp)
		{
			free(*lineptr);
			*lineptr = NULL;
			free(tmp);
			return (clean_save(save));
		}
		free(*save);
		*save = tmp;
		return (1);
	}
	*lineptr = ft_strdup(*save);
	if (!*lineptr)
		return (clean_save(save));
	free(*save);
	*save = NULL;
	return (0);
}

int	get_next_line(int fd, char **lineptr)
{
	static char		*save[OPEN_MAX];
	char			buff[BUFFER_SIZE + 1];
	char			*newline;
	size_t			alloc_size;
	ssize_t			read_size;

	if ((BUFFER_SIZE < 1) || (fd > OPEN_MAX) || (fd < 0) || !lineptr)
		return (-1);
	buff[BUFFER_SIZE] = '\0';
	if (!check_save(&save[fd]))
		return (-1);
	alloc_size = ft_strlen(save[fd]);
	while (1)
	{
		read_size = read(fd, buff, BUFFER_SIZE);
		if (read_size < 0)
			return (clean_save(&save[fd]));
		alloc_size += (size_t)read_size;
		if (!real_cat(&save[fd], buff, alloc_size + 1))
			return (clean_save(&save[fd]));
		newline = ft_strchr(save[fd], '\n');
		if (newline != NULL || read_size < BUFFER_SIZE)
			return (takeout_line(lineptr, &save[fd], newline));
	}
}
