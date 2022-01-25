/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:53:53 by gpaeng            #+#    #+#             */
/*   Updated: 2022/01/25 00:31:44 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libftx.h"

struct	Jop {
	char	**envp;
}jop;

/*
**utils
*/
void	*builtin_set_malloc(size_t nmemb, int size);
void	ft_free_arr(char **arr);
int		ft_cnt_arg(char *args[]);
char	*ft_get_env(char *path_n);
int		ft_check_arg_form(char *args[]);
void	ft_add_path(char **path_v, char *slash);

/*
**builtin_cd.c
*/
void	builtin_cd(char *args[]);

/*
**builtin_echo.c
*/
void	builtin_echo(char *args[]);

/*
**builtin_env.c
*/
void	builtin_env(char *args[]);

/*
**builtin_exit.c
*/
void	builtin_exit(char *args[]);

/*
**builtin_export.c
*/
void	builtin_export(char *args[]);

/*
**builtin_pwd.c
*/
void	builtin_pwd(char *args[]);

/*
**builtin_unset.c
*/
void	builtin_unset(char *args[]);

#endif
