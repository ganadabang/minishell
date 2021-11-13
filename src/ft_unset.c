/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:49:34 by gpaeng            #+#    #+#             */
/*   Updated: 2021/11/12 17:31:22 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_check_env(char *args)
{
    int i;

    i = 0;
    while (job.envp[i])
    {
        if (!(ft_strncmp(job.envp[i], args, ft_strlen(args))))
        {
            return (i);
        }
        i++;
    }
    return (-1);
}

char *ft_set_malloc(int size)
{
    char *arr;
    int i;

    i = 0;
    if (!(arr = (char *)malloc(sizeof(char) * size)))
        return (0);
    while (i < size)
    {
        arr[i] = 0;
        i++;
    }
    arr[i] = '\0';
    return (arr);
}

int     ft_cnt_arg(char *args[])
{
    int i;

    i = 0;
    while (args[i])
    {
        i++;
    }
    return (i);
}

void    ft_free_arr(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void    ft_remove_env(char *args[], int env_line)
{
    char **env;
    int cnt_env_arr;
    int i;
    int envp_i;
    
    cnt_env_arr = ft_cnt_arg(job.envp) - 1;
    env = ft_set_malloc(cnt_env_arr);
    i = 0;
    envp_i = 0;
    while (i < cnt_env_arr)
    {
        if (i != env_line)
        {
            env[i] = ft_strdup(job.envp[envp_i]);
            i++;
        }
        envp_i++;
    }
    ft_free_arr(job.envp);
    job.envp = env;
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
            ft_remove_env(args, env_line)
        }
        i++;
    }
}