/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:30:14 by gpaeng            #+#    #+#             */
/*   Updated: 2021/11/12 17:31:16 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char envp[3][50] = 
{
    "HOME=/hello/world",
    "PWD=/jjjj/ddd",
    "OLDPWD=/jjjj/ddd"
};

void ft_add_path(char **path_v, char slash)
{ // Put the slash
    char *tmp;

    tmp = ft_strjoin(*path_v, &slash);
    free(*path_v);
    *path_v = tmp;
}

static void ft_do_chdir(char *path_v, char *oldpwd)
{
    char *pwd;

    chdir(path_v);
    pwd = ft_get_pwd("PWD");
    ft_update_env("PWD", pwd);
    ft_update_env("OLDPWD", oldpwd);
    free(pwd);
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

char    *ft_get_pwd(char *path_n)
{
    char buffer[4096];
    char *pwd;

    if (getcwd(buffer, 4096) == 0)
    {
        pwd = ft_get_env(path_n);
        return (pwd);
    }
    pwd = ft_strdup(buffer);
    return (pwd);
}

void    ft_update_env(char *path_n, char *path_v)
{
    char *path;
    int i;
    int path_name_num;
    
    i = 0;
    while (job.envp[i])
    {
        path_name_num = 0;
        while (job.envp[i][path_name_num] != '=')
            path_name_num++;
        if (ft_strncmp(job.envp[i], path_n) == 0) // 같은 경우
        {   
            path = ft_set_malloc(ft_strlen(job.envp[i]));
            ft_strlcpy(path, job.envp[i], path_name_num + 1);
            ft_strlcpy(path, path_v, ft_strlen(path_v) + 1);
            free(job.envp[i]);
            job.envp[i] = path;
        }
        i++;
    }
}

int ft_check_pathname(char *a, char *b)
{
    int i;
    
    i = 0;
    if (ft_strlen(a) != ft_strlen(b))
        return (0);
    while (i < (int)ft_strlen(a))
    {
        if (a[i] != b[i])
            return (0);
        i++;
    }
    return (1);
}

char *ft_get_env(char *path_n)
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
        ft_strlcpy(path_value, job.envp[i] + j + 1, ft_strlen(job.envp[i]) - j);
        if (ft_check_pathname(path_name, path_n))
        {
            free(path_name);
            return (path_value);
        }
        free(path_name);
        free(path_value);
        i++;
    }
    return (0);
}

void    ft_cd(char *args[])
{
    char **splitted_path;
    char *pwd;
    char *path_value;
    int i;
    
    args++;
    i = 0;
    splitted_path = ft_split(*args, '/');
    pwd = ft_get_pwd();
    if (!splitted_path)
    {
        path_value = ft_get_env("HOME");
        ft_do_chdir(path_value, pwd);
    }
    while (splitted_path[i])
    {
        ft_add_path(&splitted_path[i], '/');
        ft_do_chdir(splitted_path[i], pwd);
        i++;
    }
}
