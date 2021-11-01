/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:32:39 by gpaeng            #+#    #+#             */
/*   Updated: 2021/11/01 16:32:41 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
#include "minishell.h"

// PWD 환경변수
//https://www.unixtutorial.org/pwd-command-and-pwd-variable/
//buffer 크기 지정
//https://stackoverflow.com/questions/3033771/file-i-o-with-streams-best-memory-buffer-size
void ft_pwd(void) 
{
	char buf[4096];

	if (getcwd(buf, 4096) == NULL)
		exit(1); // 비정상 종료 => error
	printf("%s\n", buf);
}
