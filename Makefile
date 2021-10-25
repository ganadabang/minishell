# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 19:17:03 by hyeonsok          #+#    #+#              #
#    Updated: 2021/10/25 21:20:52 by hyeonsok         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES : .c .o

#### Start of system configuration section. ####
srcdir = ./src

CC = clang

LIBS =
CFLAGS = $(include_dirs) -Wall -Werror -Wextra
include_dirs = -Iinclude
#### End of system configuration section. ####

NAME = minishell

SRCS	= main.c
OBJS	= $(SRCS:.c=.o)
OBJDIR	= ./obj/
SRCDIR	= ./src/
OBJS	= $(addprefix $(OBJDIR), main.o)








.PHONY:	$(OBJS)
$(OBJS): | $(OBJDIR)
$(OBJDIR):
			mkdir $(OBJDIR)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
			$(COMPILE.c) $(OUTPUT_OPTION) $<

.PHONY:		all
all:		$(NAME)

.PHONY:		NAME
$(NAME):	$(OBJS)
			$(CC) $(OBJS) -o $(NAME)

.PHONY:		clean
clean:
			$(RM) -r $(OBJS)

.PHONY:		fclean
fclean:		clean
			$(RM) -r $(NAME)

.PHONY:		re
re:
			$(MAKE) fclean
			$(MAKE)
