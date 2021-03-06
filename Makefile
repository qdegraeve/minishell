# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/07 08:41:32 by qdegraev          #+#    #+#              #
#    Updated: 2016/03/31 14:45:21 by qdegraev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


LIBPATH = libft
LIB = $(LIBPATH)/libft.a

NAME = minishell

CC = clang

VPATH = src:../include

INCLUDES = include/

CFLAGS = -g -Wall -Wextra -Werror

LDFLAGS = -L libft -lft

SRC =  env.c \
	set_unset_env.c \
	minishell.c \
	get_path.c \
	command_cd.c \
	tools.c \
	prompt.c \
	get_env.c \
	do_fork.c \

OBJ = $(SRC:.c=.o)

all: $(LIB) $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INCLUDES)

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

