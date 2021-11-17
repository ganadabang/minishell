/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 19:25:36 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/11/17 18:02:13 by gpaeng           ###   ########.fr       */
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
	ft_exit(argv);
	// int i =0;
	// while (jop.envp[i])
	// {
	// 	printf("?>> %s\n", jop.envp[i]);
	// 	i++;
	// }
	// ft_export(argv);
	// printf("================\n");
	// i =0;
	// while (jop.envp[i])
	// {
	// 	printf("?>> %s\n", jop.envp[i]);
	// 	i++;
	// }
	// ft_env(argv);
}