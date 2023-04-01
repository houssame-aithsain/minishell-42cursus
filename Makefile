# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/01 21:04:27 by gothmane          #+#    #+#              #
#    Updated: 2023/04/01 21:04:28 by gothmane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = ./libft

LIB = ./libft/libft.a

NAME = minishell

SRC = minishell.c

OBJCTS = ${SRC:.c=.o}

make :
	make -C ${LIBFT}

all : ${OBJCTS}
	gcc -lreadline ${SRC} ${LIB} -o ${NAME}

re : fclean all

fclean:
	rm -rf *.o ${NAME}