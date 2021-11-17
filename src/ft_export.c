/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:53:12 by gpaeng            #+#    #+#             */
/*   Updated: 2021/11/17 19:55:02 by gpaeng           ###   ########.fr       */
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
        path_value = ft_set_malloc(ft_strlen(jop.envp[i]) - j + 1);
        ft_strlcpy(path_name, jop.envp[i], j + 1);
        ft_strlcpy(path_value, jop.envp[i] + j + 1, ft_strlen(jop.envp[i]) - j);
        printf("declare -x %s=\"%s\"\n", path_name, path_value);
        free(path_name);
        free(path_value);
        i++;
    }
}

int ft_check_key_value_form(int i, int j, char *args[])
{
    return (j == 0 || j == 1 || j == (int)ft_strlen(args[i]) + 1);
}

int ft_str_digit_check(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1); //전체 문자열
}

char *find_path_name(int i, int j, char *args[])
{
    char *path_name;

    path_name = ft_set_malloc(j + 1);
    ft_strlcpy(path_name, args[i], j + 1);
    return (path_name);
}

int ft_check_key_form(int i, int j, char *args[])
{
    char *path_name;

    path_name = ft_set_malloc(j + 1);
    ft_strlcpy(path_name, args[i], j + 1);
    if (ft_str_digit_check(path_name))
        return (0);
    return (1);
}

int ft_check_arg_form(char *args[])
{
    char *path_name;
    int i;
    int j;

    i = 1;
    while (args[i])
    {
        j = 0;
        if (args[i][j] != '=')
            j++;
        if (ft_check_key_value_form(i, j, args)) //없는 것
            return (0);
        if (ft_check_key_form(i, j, args)) //숫자가 있는 경우
        {
            path_name = find_path_name(i, j, args);
            printf("export: not an identifier: %s\n", path_name);
            return (0);
        }
        i++;
    }
    return (1);
}


void ft_update_env_export(char *args[])
{
    char **env;
    int cnt_env_arr;
    int i;

    cnt_env_arr = ft_cnt_arg(jop.envp);
    env = (char **)malloc(sizeof(char *) * (cnt_env_arr + 1));
    if (!env)
        return ;
    i = 0;
    if (ft_check_arg_form(args)) //key=value형태
    {
        while (jop.envp[i] && i < cnt_env_arr)
        {
            env[i] = ft_strdup(jop.envp[i]);
            i++;
        }
        env[i] = ft_strdup(args[1]);
        // ft_free_arr(jop.envp); //test할때는 주석처리 => 할당을 어떻게 하냐에 따라 달라집니다.
        jop.envp = env;
    }
    return ;
}

void ft_export(char *args[])
{
    if (ft_cnt_arg(args) == 1)
        ft_print_env_export();
    else if (ft_cnt_arg(args) >= 2)
        ft_update_env_export(args);
}