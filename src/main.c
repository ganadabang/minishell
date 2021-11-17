/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 19:25:36 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/11/17 15:35:47 by gpaeng           ###   ########.fr       */
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

int main(int argc, char *argv[], char *env[])
{
	jop.envp = env;
	(void)argc;
	// ft_echo(argv);
	// ft_pwd(argv);
	// ft_env(argv);
	ft_exit(argv);
	// printf("%s", getenv("PATH"));
	// char *a;
	// char *b = "env=/ddd/ddd/fff";
	// a = ft_set_malloc(4);
	// ft_strlcpy(a, b, 4);
	
	// printf(">> \"%s\"\"%s\"\n", a, b);
}