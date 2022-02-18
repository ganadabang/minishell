/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mush.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 17:25:14 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/19 00:20:11 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUSH_H
# define MUSH_H

# include <termios.h>
# include "libhx/array.h"
# include "libhx/buffer.h"

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

typedef struct s_mush_var
{
	char	*key;
	char	*value;
}	t_mush_var;

typedef struct s_word {
	char	*str;
	int		word_type;
}	t_word;

typedef struct s_token {
	char				*str;
	enum e_mush_token	type;
}	t_token;

typedef struct s_file {
	char			*name;
	enum e_iotype	io_type;
	int				oflag;
	int				fd;
}	t_file;

typedef struct s_job {
	t_array	pipeline;
	int		status;
}	t_job;

typedef struct s_state {
	struct termios	term;
	t_job			job;
	t_array			envlist;
	char			*pwd;
	char			*old_pwd;
	int				exit;
	char			*last_status;
}	t_state;

typedef struct s_proc {
	char	*name;
	t_array	argv;
	t_array	io_files;
	pid_t	pid;
	int		status;
	int		(*fn_builtin)(t_state *, int, char *[]);
	int		stdin;
	int		stdout;
}	t_proc;

void	debug_pipeline(t_array *pipeline);
void	mush_fatal(const char *str);
char	*mush_get_env(t_state *state, char *key);
void	mush_set_env(t_state *state, char *key, char *value);
void	mush_put_env(t_state *state, char *str);
void	mush_unset_env(t_state *state, char *key);


#endif
