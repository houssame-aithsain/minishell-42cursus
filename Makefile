LIBFT = ./libft

LIB = ./libft/libft.a

NAME = minishell

SRC = minishell.c readl_and_exec.c utils.c nodepush.c get_value_from_variable.c ./builtin/ft_export.c ./builtin/builtins_func.c

OBJCTS = ${SRC:.c=.o}

make :
	make -C ${LIBFT}

all : ${OBJCTS}
	gcc  -lreadline ${SRC} ${LIB} -o ${NAME}

re : fclean all

clean :
		rm -f *.o

fclean: clean
	rm -rf *.o ${NAME}