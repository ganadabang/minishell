/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:53:53 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/17 03:08:22 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "mush.h"

struct s_builtin {
	char	*name;
	int		(*builtin)(t_state *, int, char *[]);
};

/** src/builtin_*.c */
int		builtin_cd(t_state *state, int argc, char *argv[]);
int		builtin_echo(t_state *state, int argc, char *argv[]);
int		builtin_env(t_state *state, int argc, char *argv[]);
int		builtin_exit(t_state *state, int argc, char *argv[]);
int		builtin_export(t_state *state, int argc, char *argv[]);
int		builtin_pwd(t_state *state, int argc, char *argv[]);
int		builtin_unset(t_state *state, int argc, char *argv[]);
int		builtin_search(t_proc *proc);

/** utils */
int		mush_regex(char *args[]);
void	mush_env_realloc(t_state *state);

#endif
