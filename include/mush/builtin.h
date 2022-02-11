/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:53:53 by gpaeng            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/02/10 20:02:01 by gpaeng           ###   ########.fr       */
=======
/*   Updated: 2022/02/11 16:05:44 by hyeonsok         ###   ########.fr       */
>>>>>>> d0c4100a9a1f68d99e757a09b883160ad82f1c32
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

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
int		ft_check_arg_form(char *args[]);
void	ft_add_path(char **path_v, char *slash);
void	ft_strswap(char **str1, char **str2);
int	bubble_sort_envp(char **str);

int	builtin_cd(t_state *state, int argc, char *argv[]);
int	builtin_echo(t_state *state, int argc, char *argv[]);
int	builtin_env(t_state *state, int argc, char *argv[]);
int	builtin_exit(t_state *state, int argc, char *argv[]);
int	builtin_export(t_state *state, int argc, char *argv[]);
int	builtin_pwd(t_state *state, int argc, char *argv[]);
int	builtin_unset(t_state *state, int argc, char *argv[]);
int	builtin_search(t_proc *proc);


#endif
