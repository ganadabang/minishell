/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:38:15 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/27 19:39:12 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern char **environ;
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "libftx.h"

enum	e_op_type {
	OP_PIPE,
	OP_LESS,
	OP_GREAT,
	OP_DLESS,
	OP_DGREAT
};

enum	e_word_type {
	WORD,
	WORD_CMD,
	WORD_IO_FILE,
	WORD_HERE_END
};

enum	e_io_type {
	IO_IN,
	IO_OUT,
	IO_APPEND,
	IO_HERE
};

typedef struct s_file {
	char			*name;
	enum e_io_type	type;
}	t_file;

typedef struct s_proc {
	char	*name;
	char	**argv;
	t_array	io_files;
	pid_t	pid;
	int		(*fp_builtin)(char *[]);
	int		status;
}	t_proc;

typedef struct s_job {
	t_array	procs;
	int		status;
}	t_job;

typedef struct s_state {
	struct termios	term;
	t_job			job;
	char			**envp;
	int				last_status;
}	t_state;

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

void	mush_backup_default()
{

}

	mush_state_create()
	loop
	{
		mush_setup_interactive()
		input = readline()
		mush_setup_meanwhile_exec()
		mush_parser_create()
		mush_state_with_parser()
		mush_job_create();
		job->pipeline = mush_parse_line() {
			loop
			{
				pretokens = parser_tokenize //give token_type; word or redirection or pipe
				tokens = mush_parser_tokenize() { // give word_type or redirection_type
					let buffer
					let token_array
					while input != '\0'
					{
						pretoken = get_next_pretoken
						if (token_type == redirection)
						{
							type = get_io_redirection_type();
							if (type == io_here)
							{
								io_here_end = get_next_word();
								parser_read_heredoc();
								token_array_push("./.here_tmp")
								continue;
							}
							token_array_push(get_next_word(), redirection_type);
						}
						if (pretoken with no quoting)
							word = pretoken_to_word_string(no_single_quoted)
						else (pretoken with quoting)
						{
							words = pretoken_to_words()// splited "" '' ex hell"o   world"'!' => hell, "o   world", '!'
							foreach words
							{
								str = quoting_to_word_string(pretoken, is_single_quoted?)
								buffer_putstr(str)
								free(str)
							}
							token = buffer_withdraw()
							token_array_push(token);
						}
					}
				}
				parser_create_pipeline(parser)
				{
					...
				}
				parser_synstax_error()
				{
					...
				}
			
		mush_state_destroy_parser()
		mush_state_with_job()
		mush_execute_job()
		{
			if mush_builtin_search
				return mush_execute_builtin()
			return mush_execute_pipeline() {
			loop
			{
				process_open_pipe()
				fork()
				if errno != 0 then error
				if pid == 0
					process_command_expansion()
					process_io_redirect()
					if mush_builtin_search() return exit(process_execute_builtin())
						process_execute_simple_command()//child exits
				if (pid > 0)
					process_close_pipe()
			}
			close(last_pipe in fd)
			pl_update_status()
			return (last_status);
		}
		}
		mush_newline_when_signaled
	}
	mush_state_destroy()
	mush_setup_default()
	mush_print_exit()
	return ;
}

inline void	mush_backup_default(struct termios *term)
{
	tcgetattr(STDOUT_FILENO, term);
}
int	main(int argv, char *argv[], char *envp[])
{
	struct termios	term;

	mush_backup_term_default(&term);

	//signal
	mush_setup_
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
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
	
}