/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 19:25:36 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/11/17 21:24:07 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


extern char **environ;

int main(int argc, char *argv[], char *env[])
{
	jop.envp = env;
	(void)argc;
	
	// ft_echo(argv);
	// ft_pwd(argv);
	// ft_exit(argv);
	// ft_export(argv);
	int i;
	i = 0;
	while (jop.envp[i])
	{
		printf("before >>>> %s\n", jop.envp[i]);
		i++;
	}
	ft_unset(argv);
	i = 0;
	while (jop.envp[i])
	{
		printf("after >>>> %s\n", jop.envp[i]);
		i++;
	}
	// ft_env(argv);
}