/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 19:25:36 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/11/19 16:57:13 by gpaeng           ###   ########.fr       */
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
	// ft_unset(argv);
	// ft_env(argv);
	ft_cd(argv);
	
	// int i = 0;
	// while (jop.envp[i])
	// {
	// 	printf(">>>> %s\n", jop.envp[i]);
	// 	i++;
	// }
	ft_pwd(argv);
}