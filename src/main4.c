/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:47:55 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/27 23:14:11 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "libftx.h"

extern char	**environ;

enum	e_iotype {
	IO_IN,
	IO_OUT,
	IO_APPEND,
	IO_HERE
};

typedef struct s_proc {
	char	*name;
	char	**argv;
	t_array	io_files;
	pid_t	pid;
	int		status;
	int		(*fp_builtin)(char *[]);
}	t_proc;

typedef struct s_file {
	char	*name;
	int		io_type;
}	t_file;

typedef struct s_job {
	t_array	*procs;
	int		status;
}	t_job;

typedef struct s_state {
	struct termios	term;
	t_job			*job;
	char			**envp;
	char			*pwd;
	char			*old_pwd;
	int				exit;
	int				last_status;
}	t_state;

typedef struct s_parser
{
	char	*input;
	t_array	tokens;
}	t_parser;

void	mush_sighandler(int signum)
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
	return ;
}

void	mush_state_create(t_state *state, char **envrion)
{
	tcgetattr(STDOUT_FILENO, &state->term);
	state->job = NULL;
	state->envp = environ;//?
	state->exit = -1;
	state->last_status = 0;
}

void	mush_mode_interactive(struct termios *term)
{
	signal(SIGINT, mush_sighandler);
	term->c_lflag &= ~ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW ,term);
}

void	mush_mode_executive(struct termios *term)
{
	signal(SIGINT, SIG_IGN);
	term->c_lflag |= ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW ,term);
}

void	mush_signal(void)
{
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGWINCH, mush_sighandler);
	return ;
}

void	mush_term_restored(struct termios *term)
{
	term->c_lflag |= ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW ,term);
}

t_job	*mush_parse_line(char *input)
{
	return (NULL);
}

int	mush_parse(t_state *state, char *input)
{
	t_parser	parser;

	if (input == NULL)
	{
		state->exit = 0;
		return (-1);
	}
	free(input);
	return (0);
	// add_history(input);
	// parser.input = input;
	// if (mush_parser_tokenize(&parser) == -1)
	// {
	// 	state->last_status = 1;
	// 	free(input);
	// 	return (-1);
	// }
	// mush_job_create(&parser, state);
	// mush_parser_destroy(&parser);
	// if (mush_syntax_check(&state.job) == -1)
	// {
	// 	state->last_status = 258;
	// 	mush_job_destory(&state.job);
	// 	return (-1);
	// }
	// return (0);
}

int	main(int argc, char *argv[])
{
	t_state	state;
	int		status;
	char	*input;


	mush_state_create(&state, environ);
	mush_signal();
	while (state.exit == -1)
	{
		mush_mode_interactive(&state.term);
		input = readline("mush+> ");
		if (mush_parse(&state, input) == -1)
			continue ;
		mush_mode_executive(&state.term);
		status = mush_execute(&state);
		if (status > 128)
			write(1, "\n", 1);
	}
	mush_term_restored(&state.term);
	write(1, "exit\n", 5);
	return (0);
}
