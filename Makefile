# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 19:17:03 by hyeonsok          #+#    #+#              #
#    Updated: 2021/11/12 13:34:37 by gpaeng           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra

INCLUDES = -I ./include/ -I /Users/$(USER)/.brew/opt/readline/include/
LIBS = -L /Users/$(USER)/.brew/opt/readline/lib/ -lreadline

OBJ		=	main.o		\
			ft_memcpy.o	\
			ft_split.o	\
			ft_strdup.o	\
			ft_strjoin.o\
			ft_strlcpy.o\
			ft_strlen.o	\
			ft_echo.o	\
			
OBJS	= $(addprefix $(OBJDIR)/, $(OBJ))

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
