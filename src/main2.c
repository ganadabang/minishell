/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:51:09 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/24 23:39:25 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush/exec.h"

extern char **environ;

int	main(void)
{
	t_job		job = (t_job){{0}, environ, 0, 0};
	t_file		io_file = {"outfile", IO_OUT};
	t_proc		proc1 = {"/bin/ls", (char *[]){"/bin/ls", "-l", NULL}, {0}, 0};
	t_proc		proc2 = {"/usr/bin/grep", (char *[]){"usr/bin/grep", "a.out", NULL}, {0}, 0};
	
	//lexer
	//parser
	hx_array_push(&proc1.io_redirect, &io_file);
	hx_array_push(&job.pipeline, &proc1);
	hx_array_push(&job.pipeline, &proc2);

	//executor
	//sync exit state
	return (0);
}
