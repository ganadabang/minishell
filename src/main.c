// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2021/10/25 19:25:36 by hyeonsok          #+#    #+#             */
// /*   Updated: 2022/01/24 22:49:08 by hyeonsok         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// // #include "minishell.h"
// # include <stdio.h>
// # include <stdlib.h>
// # include <unistd.h>
// # include <sys/wait.h>
// # include <fcntl.h>
// # include <term.h>
// # include <termios.h>
// # include <errno.h>
// # include <string.h>
// # include <stdbool.h>
// # include "array.h"
// # include "buffer.h"

// # include <readline/readline.h>
// # include <readline/history.h>

// static inline int save_default(struct termios *term)
// {
// 	return (tcgetattr(STDOUT_FILENO, term));
// }

// static inline int restore_default(struct termios *term)
// {
// 	return (tcsetattr(STDOUT_FILENO, TCSANOW, term));
// }

// typedef struct s_state {
// 	struct termios	term;
// 	int				term_fd;
// 	int				interactive;
// }	t_state;


// struct s_process {
// 	char	*name;
// 	char	**args;
// }	t_process;

// enum	e_word_type {
// 	WORD,
// 	WORD_COMMAND,
// 	WORD_NAME,
// 	WORD_HERE_END
// };

// enum	e_io_type {
// 	IO_LESS,
// 	IO_GREAT,
// 	IO_DLESS,
// 	IO_DGREAT
// };

// size_t	get_op_range(const char *input)
// {
// 	if (strncmp("<<", input, 2) == 0 || strncmp(">>", input, 2) == 0)
// 		return (2);
// 	if (*input == '<' || *input == '>' || *input == '|')
// 		return (1);
// 	return (0);
// }

// int main(int argc, char *argv[])
// {
// 	struct termios	term;
// 	int		quote_unclosed;
// 	int		dquote_unclosed;
// 	char	*input;
// 	t_buf	buf;
// 	t_array	tokarr;

// 	quote_unclosed = false;
// 	dquote_unclosed = false;
// 	memset(&buf, 0, sizeof(buf));
// 	memset(&tokarr, 0, sizeof(t_array));
// 	input = readline("prompt> ");
// 	{
// 		size_t	size;
	
// 		if (!input)
// 			return (1);
// 		input += strspn(input, " \t\n");
// 		while (*input)
// 		{
// 			if (*input == '\'')
// 			{
				
// 				input += 1;
// 			}
// 			else if (*input == '\"')
// 			{
// 				dquote_unclosed = true;
// 				hx_buffer_putchar(&buf, '"');
// 				input += 1;
// 			}
// 			if (quote_unclosed || quoted_unclosed)
// 			{
// 				size = strcspn(input, "\"'");
// 				if (input[size] == '\0')
// 					break ;
// 				hx_buffer_putstr(&buf, input, ++size);
// 				input += size;
// 				if (*input == '\'' && !dquoted_unclosed)
// 					quote_unclosed = false;
// 				if (*input == '"' && !quoted_unclosed)
// 					dquote_unclosed = false;
// 				continue ;
// 			}
// 			if (*input == '<' || *input == '>' || *input == '|')
// 			{
// 				size = get_op_range(input);
// 				hx_buffer_putstr(&buf, input, size);
// 				hx_buffer_putchar(&buf, '\0');
// 				hx_arrayffefew_push(&tokarr, hx_buffer_withdraw(&buf));
// 				input += size;
// 				continue ;
// 			}
// 			hx_array_push(&tokarr, hx_buffer_withdraw(&buf));
// 			input += strspn(input, ' \t\n');
// 			continue ;
// 			}
// 			hx_buffer_putchar(&buf, '\0');
// 			hx_array_push(&tokarr, hx_buffer_withdraw(&buf));
// 		}
// 	}
// 	hx_buffer_cleanup(&buf);
// 	hx_array_cleanup(&tokarr);
// 	return (0);
// }
