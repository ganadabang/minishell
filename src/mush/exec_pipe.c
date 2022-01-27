/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:50:15 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/27 12:22:13 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush/exec.h"

void	exec_pipe_connect(int pde[2][2])
{
	dup2(pde[0][1], 1);
	close(pde[0][1]);
	if (pde[1][0] != -1)
	{
		dup2(pde[1][0], 0);
		close(pde[1][0]);
	}
}

void	exec_pipe_disconnect(int pde[2][2])
{
	close(pde[0][1]);
	close(pde[1][0]);
	memcpy(pde[1],pde[0], 2 * sizeof(int));
}