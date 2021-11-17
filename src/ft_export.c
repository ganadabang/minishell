/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:53:12 by gpaeng            #+#    #+#             */
/*   Updated: 2021/11/17 15:20:23 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_print_env_export(void)
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
        printf("declare -x %s\"%s\"\n", path_name, path_value);
        free(path_name);
        free(path_value);
        i++;
    }
}

int ft_check_arg_form(char *args[])
{
    int i;
    int j;
    
    i = 1;
    while (args[i])
    {
        j = 0;
        if (args[i][j] != '=')
            j++;
        if (j == 0 || j == (int)ft_strlen(args[i])) //없는 것
            return (0);
        i++;
    }
    return (1);
}

void ft_update_env_export(char *args[])
{
    char **env;
    int cnt_env_arr;
    int i;
    int envp_i;

    cnt_env_arr = ft_cnt_arg(jop.envp) + 1;
    env = (char **)ft_set_malloc(cnt_env_arr);
    i = 0;
    envp_i = 0;
    if (ft_check_arg_form(args)) //key=value형태
    {
        while (i < cnt_env_arr)
        {
            env[i] = ft_strdup(jop.envp[i]);
            i++;
        }
        env[i] = ft_strdup(args[1]);
        ft_free_arr(jop.envp);
        jop.envp = env;
    }
}

void ft_export(char *args[])
{
    if (ft_cnt_arg(args) == 1)
        ft_print_env_export();
    else if (ft_cnt_arg(args) >= 2)
        ft_update_env_export(args);
}