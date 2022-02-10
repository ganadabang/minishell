/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:47:55 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/10 15:57:35 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

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
			printf("io_type: %d\tfilename: %s\n", \
				((t_file *)io_files->data[j])->io_type, \
				((t_file *)io_files->data[j])->name);
			++j;
		}
		++i;
	}
	return ;
}

void	mush_state_create(t_state *state_ref, char **envp)
{
	ft_memset(state_ref, 0, sizeof(t_state));
	tcgetattr(STDOUT_FILENO, &state_ref->term);
	state_ref->envp = envp;
	state_ref->exit = -1;
	state_ref->last_status = 0;
	state_ref->pwd = getenv("PWD");
	state_ref->old_pwd = getenv("OLDPWD");
}

int	main(int argc, char *argv[], char *envp[])
{
	t_state	state;
	
	mush_state_create(&state, envp);
	mush_prompt_signal();
	while (state.exit == -1)
	{
		mush_prompt_interactive(&state.term);
		if (mush_parser_readline(&state) < 0)
			continue ;
		mush_prompt_executive(&state.term);
		mush_execute(&state);
	}
	mush_prompt_restored(&state.term);
	write(1, "exit\n", 5);
	return (0);
}
