# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/07 08:41:32 by qdegraev          #+#    #+#              #
#    Updated: 2016/03/17 18:52:03 by qdegraev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


LIBPATH = ft_printf
LIB = $(LIBPATH)/libftprintf.a

NAME = minishell

CC = gcc

VPATH = src:../include

INCLUDES = include/

CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -L ft_printf -lftprintf

SRC =  env.c \
	minishell.c \
	get_path.c \
	command_cd.c \
	tools.c

OBJ = $(SRC:.c=.o)

all: $(LIB) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCLUDES) -o $@ -c $<

$(LIB):
	make -C $(LIBPATH)

clean:
	make clean -C $(LIBPATH)
	rm -f $(OBJ)

fclean: clean
	make fclean -C $(LIBPATH)
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean flcean

