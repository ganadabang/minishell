/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_expn_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:06:43 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 16:59:08 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include "libft.h"
#include "mush/exec.h"

static void	exec_expn_check_path(char **cmd_path_ref, char *path, char *name)
{
	char	**pathv;
	char	*slash_name;
	char	*cmd_path;
	size_t	i;

	slash_name = ft_strjoin("/", name);
	pathv = ft_split(path, ":");
	if (slash_name == NULL || pathv == NULL)
		mush_fatal("malloc");
	cmd_path = NULL;
	i = 0;
	while (pathv[i] != NULL)
	{
		cmd_path = ft_strjoin(pathv[i++], slash_name);
		stat(cmd_path, NULL);
		if (errno != ENOENT)
			break ;
		free(cmd_path);
		cmd_path = NULL;
	}
	ft_strvfree(pathv);
	free(slash_name);
	*cmd_path_ref = cmd_path;
	return ;
}

char	*exec_expn_cmd(t_state *state_ref, char *name)
{
	char	*cmd_path;
	char	*path;

	if (*name == '\0')
		return (NULL);
	path = mush_get_env(state_ref, "PATH");
	if (ft_strchr(name, '/') != NULL || path == NULL)
		return (name);
	exec_expn_check_path(&cmd_path, path, name);
	return (cmd_path);
}
