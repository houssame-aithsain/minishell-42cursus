LIBFT = ./libft

LIB = ./libft/libft.a

NAME = minishell

SRC = minishell.c readl_and_exec.c utils.c

OBJCTS = ${SRC:.c=.o}

make :
	make -C ${LIBFT}

all : ${OBJCTS}
	gcc -lreadline ${SRC} ${LIB} -o ${NAME}

re : fclean all

fclean:
	rm -rf *.o ${NAME}