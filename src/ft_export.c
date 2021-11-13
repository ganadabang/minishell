/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:53:12 by gpaeng            #+#    #+#             */
/*   Updated: 2021/11/12 16:56:56 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void ft_print_env_export(void)
{
    char *path_name;
    char *path_value;
    int i;
    int j;
    
    i = 0;
    while (job.envp[i])
    {
        j = 0;
        while (job.envp[i][j] != '=')
            j++;
        path_name = ft_set_malloc(j + 1);
        path_value = ft_set_malloc(ft_strlen(job.envp[i] - j + 1));
        ft_strlcpy(path_name, job.envp[i], j + 1);
        ft_strlcpy(path_value, job.envp[i] + j + 1, ft_strlen(envp[i]) - j);
        printf("declare -x %s\"%s\"\n", path_name, path_value);
        free(path_name);
        free(path_value);
        i++;
    }
}

void ft_check_arg_form(char *args[])
{
    int i;
    int j;
    
    i = 1;
    while (args[i])
    {
        if (args[i][j] != '=')
            j++;
        if (j == 0 || j == ft_strlen(args[i])) //없는 것
            return (0);
        i++;
    }
    return (1);
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

void ft_update_env_export(char *args[])
{
    char **env;
    int cnt_env_arr;
    int i;
    int envp_i;

    cnt_env_arr = ft_cnt_arg(job.envp) + 1;
    env = ft_set_malloc(cnt_env_arr);
    i = 0;
    envp_i = 0;
    if (ft_check_arg_form(args)) //key=value형태
    {
        while (i < cnt_env_arr)
        {
            env[i] = ft_strdup(job.envp[i]);
            i++;
        }
        env[i] = ft_strdup(args[1]);
        ft_free_arr(job.envp);
        job.envp = env;
    }
}

void ft_export(char *args[])
{
    if (ft_cnt_arg(args) == 1)
        ft_print_env_export();
    else if (ft_cnt_arg(args) >= 2)
        ft_update_env_export(args);
}