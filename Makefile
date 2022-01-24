# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 19:17:03 by hyeonsok          #+#    #+#              #
#    Updated: 2022/01/24 23:49:43 by hyeonsok         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

RM = rm -f

INCLUDES = -I ./include/ -I /Users/$(USER)/.brew/opt/readline/include/
LIBS = -L /Users/$(USER)/.brew/opt/readline/lib/ -lreadline

OBJDIR := ./obj

# ./src
OBJS		=	$(addprefix $(OBJDIR)/, \
				main2.o			\
				array.o)

# ./src/mush
OBJS		+=	$(addprefix $(OBJDIR)/, \
				exec_expn.o			\
				exec_pipe.o		\
				exec_redir.o		\
				exec_state.o		\
				exec.o)

# ./src/utils
OBJS		+=	$(addprefix $(OBJDIR)/, \
				ft_memcpy.o			\
				ft_split.o			\
				ft_strdup.o			\
				ft_cnt_arg.o		\
				ft_free_arr.o		\
				ft_set_malloc.o		\
				ft_strjoin.o		\
				ft_strlcpy.o		\
				ft_strlen.o			\
				ft_isdigit.o		\
				ft_isalpha.o		\
				ft_strncmp.o		\
				ft_get_env.o		\
				ft_check_arg_form.o	\
				ft_add_path.o)

# ./src/builtin
OBJS		+=	$(addprefix $(OBJDIR)/, \
				builtin_cd.o		\
				builtin_echo.o	\
				builtin_env.o	\
				builtin_exit.o	\
				builtin_export.o	\
				builtin_pwd.o	\
				builtin_unset.o)

SRC_DIR = ./src
SRC_UTILS_DIR = ./src/utils
SRC_BUILTIN_DIR = ./src/builtin
SRC_MUSH_DIR = ./src/mush

NAME = minishell

.PHONY:		all
all:		$(NAME)

.PHONY:		NAME
$(NAME):	$(OBJDIR) $(OBJS)
			$(CC) $(INCLUDES) $(OBJS) -o $(NAME) $(LIBS)

$(OBJDIR)/%.o : $(SRC_DIR)/%.c
			$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o : $(SRC_UTILS_DIR)/%.c
			$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o : $(SRC_MUSH_DIR)/%.c
			$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o : $(SRC_BUILTIN_DIR)/%.c
			$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

$(OBJS): | $(OBJDIR)
$(OBJDIR):
			mkdir $(OBJDIR)

.PHONY:		clean
clean:
			$(RM) -r $(OBJDIR)

.PHONY:		fclean
fclean:		clean
			$(RM) -r $(NAME)

.PHONY:		re
re:
			$(MAKE) fclean
			$(MAKE)
