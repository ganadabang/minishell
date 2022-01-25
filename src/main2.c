/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 22:51:09 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/26 00:37:19 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush/exec.h"

extern char **environ;
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <termios.h>
#include <sys/ioctl.h>

void	mush_signal(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGWINCH)
		rl_on_new_line();
}

int	main(void)
{
	//profile
	struct termios	term = {0};
	tcgetattr(STDOUT_FILENO, &term);
	

	//signal
	signal(SIGTSTP, SIG_IGN);
	signal(SIGWINCH, mush_signal);
	//TODO: lexer
	//TODO: parser
	t_job		job = (t_job){{0}, environ, -1};

	t_file		files[] = { \
		{"outfile", IO_OUT}, \
		{"infile", IO_IN}, \
		{"outfile2", IO_APPEND} \
	};

	t_proc		procs[] = { \
		{"/bin/ls", (char *[]){"/bin/ls", NULL}, {0}, 0, 0, 0},
		{"/bin/cat", (char *[]){"/bin/cat", NULL}, {0}, 0, 0, 0},
		{"echo", (char *[]){"echo", "hello", NULL}, {0}, 0, 0, 0}, 
		{"/usr/bin/grep", (char *[]){"/usr/bin/grep", "a.out", NULL}, {0}, 0, 0, 0} \
	};
	
	hx_array_push(&procs[0].io_redirect, &files[0]);
	hx_array_push(&job.pipeline, &procs[0]);

	hx_array_push(&procs[1].io_redirect, &files[2]);
	hx_array_push(&job.pipeline, &procs[1]);
	
	char		*input;
	while (1)
	{
		signal(SIGINT, mush_signal);
		//set term
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(STDOUT_FILENO, TCSANOW,&term);

		//prompt
		input = readline("mush> ");

		//restore term
		term.c_lflag |= ECHOCTL;
		tcsetattr(STDOUT_FILENO, TCSANOW, &term);

		//restore signal
		signal(SIGINT, SIG_IGN);

		//control + D
		if (!input)
			break ;
		//parse
		//TODO: mush_parser

		//execute
		mush_exec(&job);
		free(input);
		if (job.last_status > 128)
			write(1, "\n", 1);
		// TODO: mush_clean
	}
	printf("last status: %d \n", job.last_status);
	printf("exit\n");
	return (0);
}
