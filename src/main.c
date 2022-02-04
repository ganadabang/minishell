/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:47:55 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/04 19:54:59 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

extern char	**environ;

void	debug_pipeline(t_array *pipeline)
{
	size_t		i;
	size_t		j;
	char		**argv;
	size_t		maxlen;
	t_array		*io_files;
	size_t		len;

	
	printf("\npipeline->len: %zu\n", pipeline->len);
	i = 0;
	len = pipeline->len;
	while (len-- > 0)
	{
		printf("\nprocess:[%zu]\n", i);
		
		argv = (char **)((t_proc *)pipeline->data[i])->argv.data;
		maxlen = ((t_proc *)pipeline->data[i])->argv.len;
		j = 0;
		while (j < maxlen)
		{
			printf("argv[%zu]: %s\n", j, (char *)argv[j]);
			++j;
		}
		io_files = &((t_proc *)pipeline->data[i])->io_files;
		maxlen = io_files->len;
		j = 0;
		while (j < maxlen)
		{
			printf("io_type: %d\tfilename: %s\n", ((t_file *)io_files->data[j])->io_type, ((t_file *)io_files->data[j])->name);
			++j;
		}
		++i;
	}
	return ;
}

void	mush_state_create(t_state *state, char **envp)
{
	tcgetattr(STDOUT_FILENO, &state->term);
	state->envp = envp;
	state->exit = -1;
	state->last_status = 0;
}


int	main(int argc, char *argv[])
{
	t_state	state;
	int		status;
	char	*input;

	mush_state_create(&state, environ);
	mush_signal();
	while (1)
	{
		mush_mode_interactive(&state.term);
		input = readline("mush+> ");
		if (!input)
			break ;
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
