/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:28:29 by gpaeng            #+#    #+#             */
/*   Updated: 2021/11/17 16:57:39 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=lyongh00&logNo=90042249160
// 환경 변수에 대한 설명 
// job.envp 에 환경변수 값이 저장되어 있습니다.
#include "minishell.h"

int ft_check_args_env(char **args)
{
    int i;

    args++;
    i = 0;
    while (args[1][i])
    {
        if (args[1][i] == '/')
            return (1);
        i++;
    }
    return (0);
}

void ft_env(char *args[])
{
    char **env;
    
    env = jop.envp;
    if (ft_check_args_env(env))
    {
        printf("en: '%s': No such file or directory\n", args[1]);
        return ;
    }
    while (*env)
    {
        printf("%s\n", *env);
        env++;
    }
}