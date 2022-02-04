/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:50:15 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/04 17:31:03 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

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