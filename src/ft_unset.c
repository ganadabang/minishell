/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:49:34 by gpaeng            #+#    #+#             */
/*   Updated: 2021/11/17 15:23:34 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_check_env(char *args)
{
    int i;

    i = 0;
    while (jop.envp[i])
    {
        if (!(ft_strncmp(jop.envp[i], args, ft_strlen(args))))
        {
            return (i);
        }
        i++;
    }
    return (-1);
}

void    ft_remove_env(int env_line)
{
    char **env;
    int cnt_env_arr;
    int i;
    int envp_i;

    cnt_env_arr = ft_cnt_arg(jop.envp) - 1;
    env = (char **)malloc(sizeof(char *) * cnt_env_arr);
    if (!env)
        return ;
    i = 0;
    envp_i = 0;
    while (i < cnt_env_arr)
    {
        if (i != env_line)
        {
            env[i] = ft_strdup(jop.envp[envp_i]);
            i++;
        }
        envp_i++;
    }
    ft_free_arr(jop.envp);
    jop.envp = env;
}

void    ft_unset(char *args[])
{
    int i;
    int env_line;

    i = 0;
    env_line = 0;
    args++;
    while (args[i])
    {
        env_line = ft_check_env(args[i]);
        if (env_line != -1)
        {//환경변수가 있는 것
            ft_remove_env(env_line);
        }
        i++;
    }
}