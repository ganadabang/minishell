# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/26 11:13:05 by hyeonsok          #+#    #+#              #
#    Updated: 2022/02/11 14:37:32 by hyeonsok         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libfthx.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra
INCLUDE_PATH = -I include

AR = ar
RM = rm -f

LIBFT = libft.a

SRCS	=	$(addprefix src/is/,		ft_isalnum.c \
										ft_isalpha.c \
										ft_isascii.c \
										ft_isblank.c \
										ft_iscntrl.c \
										ft_isdigit.c \
										ft_isgraph.c \
										ft_islower.c \
										ft_isprint.c \
										ft_ispunct.c \
										ft_issign.c \
										ft_isspace.c \
										ft_isupper.c \
										ft_isxdigit.c \
										ft_tolower.c \
										ft_toupper.c)

SRCS	+=	$(addprefix src/io/,		ft_dputchar.c \
										ft_dputendl.c \
										ft_dputnbr.c \
										ft_dputs.c \
										ft_putchar.c \
										ft_putendl.c \
										ft_putnbr.c \
										ft_puts.c)

SRCS	+=	$(addprefix src/string/,	ft_bzero.c \
										ft_memccpy.c \
										ft_memchr.c \
										ft_memcmp.c \
										ft_memcpy.c \
										ft_memmove.c \
										ft_memset.c \
										ft_strchr.c \
										ft_strchrspn.c\
										ft_strdup.c \
										ft_strjoin.c\
										ft_strlcat.c \
										ft_strlcpy.c \
										ft_strlen.c \
										ft_strncmp.c \
										ft_strcmp.c	\
										ft_strnstr.c \
										ft_strrchr.c)

SRCS	+=	$(addprefix src/ft/,		ft_itoa.c \
										ft_split.c \
										ft_strjoin.c \
										ft_strmapi.c \
										ft_strtrim.c \
										ft_substr.c)

SRCS	+=	$(addprefix src/,			ft_atoi.c \
										ft_atoll.c \
										ft_calloc.c)

SRCS	+=	$(addprefix src/hx/,		array.c \
										buffer.c)

OBJS = $(SRCS:.c=.o)

.c.o :
			$(CC) $(CFLAGS) $(INCLUDE_PATH) -c -o $@ $<

.PHONY:		all
all:		$(NAME)

$(NAME): 	$(OBJS)
			$(AR) -rcs $@ $^

.PHONY: 	clean
clean:
			$(RM) -r $(OBJS)

.PHONY :	fclean
fclean :	clean
			$(RM) -r $(NAME)

.PHONY:		re
re: 		fclean all
