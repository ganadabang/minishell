# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 19:17:03 by hyeonsok          #+#    #+#              #
#    Updated: 2021/11/01 19:48:08 by gpaeng           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CFLAGS = -Wall -Werror -Wextra

INCLUDES = -I ./include/ -I /Users/$(USER)/.brew/opt/readline/include/
LIBS = -L /Users/$(USER)/.brew/opt/readline/lib/ -lreadline

SRCDIR := ./src
OBJDIR := ./obj
OBJS	= $(addprefix $(OBJDIR)/, main.o ft_echo.o ft_pwd.o)

NAME = minishell

.PHONY:		all
all:		$(NAME)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
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
