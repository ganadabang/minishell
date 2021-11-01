/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 19:20:34 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/11/01 19:52:29 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <term.h>
# include <termios.h>

#define UNUSED(x) (void)(x)
/*
**ft_echo.c
*/
void ft_echo(char *args[]);

/*
**ft_pwd.c
*/
void ft_pwd(char *args[]);

#endif
