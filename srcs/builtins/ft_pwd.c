/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:17:52 by gpaeng            #+#    #+#             */
/*   Updated: 2021/08/19 14:59:04 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

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

// int main(int argc, char *argv[]) {
//     ft_pwd();
// }