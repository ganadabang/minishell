/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 19:25:36 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/11/10 17:38:49 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	newline_at_interrupt(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	exit_at_eof(void)
{
	printf("exit\n");
	exit(0);
}

void	init_minishell(struct termios *term)
{
	char 			*input;
	
	term->c_lflag &= ~ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, term);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, newline_at_interrupt);
	while (1)
	{	
		input = readline("minishell> ");
		if (!input)
		{
			exit_at_eof();
		}
		add_history(input);
		free(input);
	}
}

// int main(void)
// {
// 	struct termios	term;

// 	tcgetattr(STDOUT_FILENO, &term);
// 	init_minishell(&term);
// 	tcsetattr(STDOUT_FILENO, TCSANOW, &term);
// 	return (0);
// }

extern char **environ;

int main(int argc, char *argv[])
{
	char **new_argv;
	char command[] = "cd";
	int idx;

	new_argv = (char **)malloc(sizeof(char *) * (argc + 1));

	new_argv[0] = command;

	for (idx = 1; idx < argc; idx++)
	{
		new_argv[idx] = argv[idx];
	}

	new_argv[argc] = NULL;
	if (execve("/usr/bin/cd", new_argv, environ) == -1)
	{
		printf("execve >>> 에러\n");	
	}
	
	// ft_echo(argv);
	// ft_pwd(argv);
	// ft_env(argv);
	// ft_cd(argv);
	if(chdir("include") == -1)
	{
		printf("이동 실패\n");
	}
	else {
		printf("이동 성공");
		
	}
}