/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 17:33:52 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/04 19:52:39 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <string.h>

#include "libftx.h"

enum e_mush_token {
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR,
	TOKEN_NEWLINE
};

enum	e_iotype {
	IO_IN,
	IO_OUT,
	IO_APPEND,
	IO_HERE
};

typedef struct	s_word {
	char	*str;
	int		word_type;
}	t_word;

typedef struct	s_token {
	char	*str;
	int		type;
}	t_token;

typedef struct s_file {
	char	*name;
	int		io_type;
	int		oflag;
}	t_file;

typedef struct s_job {
	t_array	pipeline;
	int		status;
}	t_job;

typedef struct s_state {
	struct termios	term;
	t_job			job;
	char			**envp;
	char			*pwd;
	char			*old_pwd;
	int				exit;
	int				last_status;
}	t_state;

typedef struct s_proc {
	char	*name;
	t_array	argv;
	t_array	io_files;
	pid_t	pid;
	int		status;
	int		(*fp_builtin)(t_state *, int, char *[]);
	int		stdin;
	int		stdout;
}	t_proc;

typedef struct s_parser
{
	t_array	token_list;
	char	*input;
	int		syntax_error;
	size_t	pos;
}	t_parser;

struct s_quoted_word {
	int		word_type;
	char	*str;
};

int		mush_parse(t_state *state, char *input);
void	mush_job_create(t_array *pipeline, t_parser *parser);

#endif
