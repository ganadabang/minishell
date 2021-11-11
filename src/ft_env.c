/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:28:29 by gpaeng            #+#    #+#             */
/*   Updated: 2021/11/11 16:48:22 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=lyongh00&logNo=90042249160
// 환경 변수에 대한 설명 
// job.envp 에 환경변수 값이 저장되어 있습니다.
#include "minishell.h"

void ft_env(char **args)
{
    char **env;
    
    (void)args;
    env = job.envp;
    while (*env)
    {
        printf("%s\n", *env);
        env++;
    }
}