# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 19:17:03 by hyeonsok          #+#    #+#              #
#    Updated: 2021/11/17 19:53:18 by gpaeng           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra

INCLUDES = -I ./include/ -I /Users/$(USER)/.brew/opt/readline/include/
LIBS = -L /Users/$(USER)/.brew/opt/readline/lib/ -lreadline

OBJ_UTILS	=	ft_memcpy.o		\
				ft_split.o		\
				ft_strdup.o		\
				ft_cnt_arg.o	\
				ft_free_arr.o	\
				ft_set_malloc.o	\
				ft_strjoin.o	\
				ft_strlcpy.o	\
				ft_strlen.o		\
				ft_isdigit.o	\
				ft_isalpha.o	\
				ft_strncmp.o	\
			
OBJ_BUILTINS	=	main.o		\
					ft_cd.o		\
					ft_echo.o	\
					ft_env.o	\
					ft_exit.o	\
					ft_export.o	\
					ft_pwd.o	\
					ft_unset.o	\
			
OBJS	= $(addprefix $(OBJDIR)/, $(OBJ_UTILS) $(OBJ_BUILTINS))

SRCDIR := ./src
SRCDIRUTILS := ./src/utils
OBJDIR := ./obj

NAME = minishell
.PHONY:		all
all:		$(NAME)

SRCS = $(addprefix $(SRCDIR), $(SRC))
		
$(OBJDIR)/%.o : $(SRCDIR)/%.c
			$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o : $(SRCDIRUTILS)/%.c
			$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

.PHONY:		NAME
$(NAME):	$(OBJDIR) $(OBJS)
			$(CC) $(INCLUDES) $(OBJS) -o $(NAME) $(LIBS)

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
