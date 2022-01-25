/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:53:53 by gpaeng            #+#    #+#             */
/*   Updated: 2022/01/26 00:01:25 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libftx.h"

struct	Jop {
	char	**envp;
}jop;

struct s_builtin {
	char	*name;
	int	(*builtin)(char *[]);
};

/*
**utils
*/
void	*ft_set_malloc(size_t nmemb, int size);
void	ft_free_arr(char **arr);
int		ft_cnt_arg(char *args[]);
char	*ft_get_env(char *path_n);
int		ft_check_arg_form(char *args[]);
void	ft_add_path(char **path_v, char *slash);


int	builtin_cd(char *args[]);
int	builtin_echo(char *args[]);
int	builtin_env(char *args[]);
int	builtin_exit(char *args[]);
int	builtin_export(char *args[]);
int	builtin_pwd(char *args[]);
int	builtin_unset(char *args[]);
int	builtin_search(const char *name, int (**f)(char *p[]));

#endif
