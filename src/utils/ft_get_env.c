/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 12:48:20 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/04 16:03:12 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush/builtin.h"

int	ft_check_pathname(char *a, char *b)
{
	int	i;

	i = 0;
	if (ft_strlen(a) != ft_strlen(b))
		return (0);
	while (i < (int)ft_strlen(a))
	{
		if (a[i] != b[i])
			return (0);
		i++;
	}
	return (1);
}

// void	ft_set_pathname_and_value(char *path_name, char *path_value, int idx, int jdx)
// {
// 	path_name = (char *)ft_set_malloc(sizeof(char), jdx + 1);
// 	path_value = (char *)ft_set_malloc(
// 			sizeof(char), ft_strlen(jop.envp[idx]) - jdx + 1);
// 	ft_strlcpy(path_name, jop.envp[idx], jdx + 1);
// 	ft_strlcpy(path_value, jop.envp[idx] + jdx + 1, ft_strlen(jop.envp[idx]) - jdx);
// }

char	*ft_get_env(char *path_n)
{
	char	*path_name;
	char	*path_value;
	int		i;
	int		j;

	i = 0;
	while (jop.envp[i])
	{
		j = 0;
		while (jop.envp[i][j] != '=')
			j++;
		path_name = (char *)ft_set_malloc(sizeof(char), j + 1);
		path_value = (char *)ft_set_malloc(
				sizeof(char), ft_strlen(jop.envp[i]) - j + 1);
		ft_strlcpy(path_name, jop.envp[i], j + 1);
		ft_strlcpy(path_value, jop.envp[i] + j + 1, ft_strlen(jop.envp[i]) - j);
		if (ft_check_pathname(path_name, path_n))
		{
			free(path_name);
			return (path_value);
		}
		free(path_name);
		free(path_value);
		i++;
	}
	return (0);
}
