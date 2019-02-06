#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/10 00:23:32 by ahonchar          #+#    #+#              #
#    Updated: 2018/05/22 18:18:19 by ahonchar         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc

FLAGS = -Wextra -Wall -Werror
# -fsanitize=address -g

SRC = main.c inline_func.c environ.c environ_p2.c inline_func_p2.c find_command.c parse_input.c ft_env.c

D_OBJ = obj/

OBJ = $(addprefix $(D_OBJ), $(SRC:.c=.o))

NAME = 21sh

LIB = ./libft/libft.a

all: libcomile $(NAME)

libcomile:
	@make -C ./libft

$(D_OBJ)%.o:%.c header.h
	$(CC) $(FLAGS) -c $< -o $@
	
$(NAME): $(D_OBJ) $(OBJ) $(LIB)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIB) -ltermcap
	@printf "\x1b[32m%s compiled\n\x1b[0m\n" $(NAME)

$(D_OBJ):
	mkdir $@

clean:
	@make -C ./libft $@
	rm -rf $(D_OBJ)

fclean: clean
	@make -C ./libft $@
	rm -rf $(NAME)
	rm -rf *~
	rm -rf \#*\#
re: fclean all