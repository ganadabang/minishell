/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:30:14 by gpaeng            #+#    #+#             */
/*   Updated: 2021/11/10 21:21:31 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char envp[3][50] = 
{
    "HOME=/hello/world",
    "PWD=/jjjj/ddd",
    "OLDPWD=/jjjj/ddd"
};

void ft_add_path(char **path, char slash)
{ // Put the slash
    char *tmp;

    tmp = ft_strjoin(*path, &slash);
    free(*path);
    *path = tmp;
}

static void ft_do_chdir(char *path)
{
    chdir(path);
}

// static void ft_set_home()
// {
    
// }

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

char *ft_get_env(char *path)
{
    char *path_name;
    char *path_value;
    int i;
    int j;
    
    i = 0;
    // while (job.envp[i])
    while (envp[i])
    {
        j = 0;
        // while (job.envp[i][j] != '=')
        while(envp[i][j] != '=')
            j++;
        path_name = ft_set_malloc(j + 1);
        // path_value = ft_set_malloc(ft_strlen(job.envp[i] - j + 1));
        // ft_strlcpy(path_name, job.envp[i], j + 1);
        // ft_strlcpy(path_value, job.envp[i] + j + 1, ft_strlen(job.envp[i]) - j);
        path_value = ft_set_malloc(ft_strlen(envp[i] - j + 1));
        ft_strlcpy(path_name, envp[i], j + 1);
        ft_strlcpy(path_value, envp[i] + j + 1, ft_strlen(envp[i]) - j);
        if (ft_check_pathname(path_name, path))
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



char    *ft_get_pwd(void)
{
    char buffer[4096];
    char *pwd;

    if (getcwd(buffer, 4096) == 0)
    {
        pwd = ft_get_env("PWD");
        return (pwd);
    }
    pwd = ft_strdup(buffer);
    return (pwd);
}

void    ft_cd(char *args[])
{
    char **splitted_path;
    char *pwd;
    int i;
    
    args++;
    i = 0;
    splitted_path = ft_split(*args, '/');
    pwd = ft_get_pwd();
    printf("%s\n", pwd);
    // if (!splitted_path)
        //환경합수에서 HOME 찾아서 경로로 보내주기
    while (splitted_path[i])
    {
        ft_add_path(&splitted_path[i], '/');
        ft_do_chdir(splitted_path[i]);
        i++;
    }
}
