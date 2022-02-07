# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/26 11:13:05 by hyeonsok          #+#    #+#              #
#    Updated: 2022/02/05 16:56:40 by gpaeng           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all bonus clean fclean re

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra

AR = ar
RM = rm -f

INCLUDES = -I./include

SRCS	=	$(addprefix src/ctype/,		ft_isalnum.c \
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
										ft_puts.c \
										get_next_line.c)

SRCS	+=	$(addprefix src/string/,	ft_bzero.c \
										ft_memccpy.c \
										ft_memchr.c \
										ft_memcmp.c \
										ft_memcpy.c \
										ft_memmove.c \
										ft_memset.c \
										ft_strchr.c \
										ft_strdup.c \
										ft_strjoin.c\
										ft_strlcat.c \
										ft_strlcpy.c \
										ft_strlen.c \
										ft_strncmp.c \
										ft_strnstr.c \
										ft_strrchr.c)

SRCS	+=	$(addprefix src/util/,		ft_itoa.c \
										ft_split.c \
										ft_strjoin.c \
										ft_strmapi.c \
										ft_strtrim.c \
										ft_substr.c)

SRCS	+=	$(addprefix src/,			ft_atoi.c \
										ft_atoll.c \
										ft_calloc.c)

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(AR) -rcs $@ $^

.c.o :
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean :
	$(RM) -r $(OBJS)

fclean : clean
	$(RM) -r $(NAME)

re : fclean all
