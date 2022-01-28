// // /* ************************************************************************** */
// // /*                                                                            */
// // /*                                                        :::      ::::::::   */
// // /*   exec.c                                             :+:      :+:    :+:   */
// // /*                                                    +:+ +:+         +:+     */
// // /*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
// // /*                                                +#+#+#+#+#+   +#+           */
// // /*   Created: 2022/01/24 14:31:28 by hyeonsok          #+#    #+#             */
// // /*   Updated: 2022/01/27 12:30:07 by hyeonsok         ###   ########.fr       */
// // /*                                                                            */
// // /* ************************************************************************** */

// // #include "mush/exec.h"
// // #include "mush/builtin.h"
// // #include "libft.h"
// // #include <sys/wait.h>
// // #include <sys/errno.h>

// // void	exec_command_on_child(t_job *job, t_proc *proc, int pde[2][2], size_t i)
// // {
// // 	int		(*f)(char *[]);
// // 	pid_t		pid;

// // 	f = NULL;
// // 	signal(SIGQUIT, SIG_DFL);
// // 	signal(SIGINT, SIG_DFL);
// // 	pipe_setup(pde, is_last_proc(i, job->pipeline.len));
// // 	io_redirect((t_file **)proc->io_redirect.data, proc->io_redirect.len);
// // 	//proc_expansioin
// // 	//filename_expansion
// // 	if(builtin_search(proc->name, &f))
// // 		exit (f(proc->argv));
// // 	execve(proc->name, proc->argv, job->envp);
// // }

// // inline	static int	_is_last_child(int d)
// // {
// // 	return (d);
// // }

// void	mush_exec_job(t_array *pipeline, size_t len)
// {
// 	t_proc		*proc;//2둘다 필요해

// 	int			(*f)(char *[]);
// 	f = NULL;
// 	proc = (t_proc *)pipeline->data[0];
// 	if (pipeline->len == 1 && builtin_search(proc->name, &f))
// 		return (exec_builtin_on_parent(pipeline->data[0]));
	
// 		pid_t	pid;
// 		int		pde[2][2];
// 		pde[1][0] = -1;
// 		for (size_t i = 0; i < len; ++i)
// 		{
// 			if (!_is_last_child(i + 1 < len))
// 				exec_pipe_connect(pde[0]);
// 			pid = fork();
// 			if (pid < 0)
// 			{
// 				perror("fork");
// 				exit(EXIT_FAILURE);
// 			}
// 			if (pid == 0)
// 				exec_command_on_child(job, job->pipeline.data[i], pde, i);
// 			proc->pid = pid;
// 			exec_pipe_disconnect(pde);
// 		}
// 		close(pde[1][0]);
// 		exec_process_status_update(job->pipeline.data, job->pipeline.len);
// 	return (exec_pipeline());
// }
