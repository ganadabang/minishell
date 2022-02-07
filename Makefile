# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 19:17:03 by hyeonsok          #+#    #+#              #
#    Updated: 2022/02/07 19:10:44 by hyeonsok         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
# CFLAGS = -Wall -Werror -Wextra -g3 
CFLAGS = -g3 
# CFLAGS = -g3 -fsanitize=address

RM = rm -f

INCLUDES	=	-I include/ -I$(shell brew --prefix readline)/include/ \
				-I lib/libft/include/

LIBS		=	-L $(shell brew --prefix readline)/lib/ -lreadline \
				-L lib/libft -lft

LIBFT		=	lib/libft/libft.a

OBJDIR := ./obj

# ./src
OBJS		=	$(addprefix $(OBJDIR)/, \
				main.o)

# ./src/builtin
OBJS		+=	$(addprefix $(OBJDIR)/, \
				builtin_cd.o		\
				builtin_echo.o	\
				builtin_env.o	\
				builtin_exit.o	\
				builtin_export.o	\
				builtin_pwd.o	\
				builtin_unset.o)

# ./src/utils
OBJS		+=	$(addprefix $(OBJDIR)/, \
				array.o					\
				buffer.o				\
				ft_cnt_arg.o			\
				ft_free_arr.o			\
				ft_set_malloc.o			\
				ft_get_env.o			\
				ft_check_arg_form.o		\
				ft_add_path.o			\
				ft_fatal.o)

# ./src/mush
OBJS		+=	$(addprefix $(OBJDIR)/, \
				prompt.o \
				parser.o \
				parser_buffer.o \
				parser_error.o \
				parser_iofile.o \
				parser_job.o \
				parser_token.o \
				exec.o \
				exec_expn.o \
				exec_pipe.o \
				exec_redir.o \
				exec_state.o \
				exec_builtin.o)




SRC_DIR = ./src
SRC_UTILS_DIR = ./src/utils
SRC_BUILTIN_DIR = ./src/builtin
SRC_MUSH_DIR = ./src/mush

NAME = minishell

.PHONY:		all
all:		libft $(NAME)

libft:		$(LIBFT)

$(LIBFT):
			make -C lib/libft/

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
			make clean -C lib/libft/
			$(RM) -r $(OBJDIR)

.PHONY:		fclean
fclean:		clean
			make fclean -C lib/libft/
			$(RM) -r $(NAME)

.PHONY:		re
re:
			$(MAKE) fclean
			$(MAKE)
