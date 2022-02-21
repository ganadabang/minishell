/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 17:33:52 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 17:47:30 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libhx/array.h"
# include "libhx/buffer.h"
# include "mush.h"

typedef struct s_parser
{
	t_array	token_list;
	t_buf	buffer;
	char	*input;
	size_t	pos;
}	t_parser;

/** 
 * src/mush/parser_buffer.c
 */
int		parser_buffer_write_quoted(t_parser *parser_ref, char quoting);
char	*parser_buffer_withdraw_operator(t_parser *parser_ref);
void	parser_buffer_write_char(t_parser *parser_ref, char ch);
char	*parser_buffer_withdraw_word(t_parser *parser_ref);

/**
 * src/mush/parser_error.c
 */
int		mush_syntax_error(t_parser *parser_ref);

/** 
 * src/mush/parser_iofile.c
 */
t_file	*parser_create_io_file(char **redir, char *str);

/**
 * src/mush/parser/pipeline.c
 */
void	mush_parser_init_pipeline(t_array *pipeline, t_parser *parser);

/**
 * src/mush/parser.c
 */
int		mush_parser_readline(t_state *state_ref);

/**
 * src/mush/parser_token.c
 */
int		mush_parser_tokenize(t_parser *parser_ref);

#endif /* PARSER_H */
