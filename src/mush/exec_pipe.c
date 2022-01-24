/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:50:15 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/24 23:01:11 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush/exec.h"

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