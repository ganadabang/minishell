/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:30:14 by gpaeng            #+#    #+#             */
/*   Updated: 2021/11/17 15:28:20 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_add_path(char **path_v, char slash)
{ // Put the slash
    char *tmp;

    tmp = ft_strjoin(*path_v, &slash);
    free(*path_v);
    *path_v = tmp;
}

void    ft_update_env(char *path_n, char *path_v)
{
    char *path;
    int i;
    int path_name_num;
    
    i = 0;
    while (jop.envp[i])
    {
        path_name_num = 0;
        while (jop.envp[i][path_name_num] != '=')
            path_name_num++;
        if (ft_strncmp(jop.envp[i], path_n, ft_strlen(path_n)) == 0) // 같은 경우
        {   
            path = ft_set_malloc(ft_strlen(jop.envp[i]));
            ft_strlcpy(path, jop.envp[i], path_name_num + 1);
            ft_strlcpy(path, path_v, ft_strlen(path_v) + 1);
            free(jop.envp[i]);
            jop.envp[i] = path;
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
    while (jop.envp[i])
    {
        j = 0;
        while (jop.envp[i][j] != '=')
            j++;
        path_name = ft_set_malloc(j + 1);
        path_value = ft_set_malloc(ft_strlen(jop.envp[i] - j + 1));
        ft_strlcpy(path_name, jop.envp[i], j + 1);
        ft_strlcpy(path_value, jop.envp[i] + j + 1, ft_strlen(jop.envp[i]) - j);
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

int ft_do_chdir(char *path_v, char *oldpwd, char **args)
{
    struct stat file_buffer;
    char *pwd;
    int file_status;
    
    if (chdir(path_v) == -1)
    {
        chdir(oldpwd);
        file_status = stat(*args, &file_buffer);
        if (file_status == -1)
            printf("minishell: cd: %s No such file or directory", args[0]);
        return (1);
    }
    pwd = ft_get_pwd("PWD");
    ft_update_env("PWD", pwd);
    ft_update_env("OLDPWD", oldpwd);
    free(pwd);
    return (0);
}

int     ft_check_args_cd(char *args[])
{
    char *path_value;
    char *pwd;
    
    if (ft_cnt_arg(args) > 1)
    {
        printf("minishell: cd: too many arguments");
        return (0);
    }
    else if (ft_cnt_arg(args) == 1)
    {
        pwd = ft_get_pwd("PWD");
        if (ft_strncmp(args[0], "-", 1) == 0)
        {
            path_value = ft_get_env("OLDPWD");
            ft_do_chdir(path_value, pwd, args);
            printf("%s\n", pwd);
            return (0);
        }
        free(pwd);
    }
    return (1);
}

void    ft_cd(char *args[])
{
    char **splitted_path;
    char *pwd;
    char *path_value;
    int i;
    
    args++;
    i = 0;
    if (!ft_check_args_cd(args))
        return ;
    splitted_path = ft_split(*args, '/');
    pwd = ft_get_pwd("PWD");
    if (!splitted_path)
    {
        path_value = ft_get_env("HOME");
        ft_do_chdir(path_value, pwd, args);
    }
    while (splitted_path[i])
    {
        ft_add_path(&splitted_path[i], '/');
        if (ft_do_chdir(splitted_path[i], pwd, args))
            break ;
        i++;
    }
    free(pwd);
    ft_free_arr(splitted_path);
}
