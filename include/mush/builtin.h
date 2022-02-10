/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:53:53 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/10 15:23:27 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libftx.h"

struct s_builtin {
	char	*name;
	int	(*builtin)(t_state *, int, char *[]);
};	

/*
**utils
*/
void	**ft_set_malloc(size_t nmemb, int size);
void	ft_free_arr(char **arr);
int		ft_cnt_arg(char *args[]);
char	*ft_get_env(char *path_n);
int		ft_check_arg_form(char *args[]);
void	ft_add_path(char **path_v, char *slash);
char	*ft_strndup(char *str, int idx);

int	builtin_cd(t_state *state, int argc, char *argv[]);
int	builtin_echo(t_state *state, int argc, char *argv[]);
int	builtin_env(t_state *state, int argc, char *argv[]);
int	builtin_exit(t_state *state, int argc, char *argv[]);
int	builtin_export(t_state *state, int argc, char *argv[]);
int	builtin_pwd(t_state *state, int argc, char *argv[]);
int	builtin_unset(t_state *state, int argc, char *argv[]);
int	builtin_search(t_proc *proc);

#endif
