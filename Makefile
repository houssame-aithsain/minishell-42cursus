# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/04 23:30:28 by hait-hsa          #+#    #+#              #
#    Updated: 2023/06/14 09:52:11 by hait-hsa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = ./libft

LIB = ./libft/libft.a

NAME = minishell

SRC = ./signales/c_d_sig.c ./parsing/if_operator.c ./parsing/errors_checker.c \
		./parsing/quotes_sanitizing/cmd_unquote.c ./parsing/quotes_sanitizing/files_unquote.c \
		./parsing/quotes_sanitizing/args_unquote.c ./parsing/quotes_sanitizing/cmd_utils.c \
		./parsing/quotes_sanitizing/args_utils.c ./parsing/utils.c ./parsing/utils2.c \
		./parsing/get_s_rd.c ./parsing/get_parse.c ./parsing/utils1.c \
		./parsing/get_s_node_args_ready.c print_error.c ./expand/get_expand_vars.c \
		./expand/keys_dup.c ./expand/utils.c minishell.c readl_and_exec.c \
		./parsing/list_builder.c ./builtin/ft_export.c ./builtin/builtins_func.c \
		./exec/sglcmd.c ./pipe/pipe.c ./redir/redir.c ./redir/redirv2.c ./redir/heredoc.c \
		./parsing/quotes_sanitizing/files_utils.c ./parsing/quotes_sanitizing/str_cp.c \
		./parsing/heredoc_cmd_finder.c ./parsing/ft_split_e.c ./expand/utils1.c ./expand/utils2.c \
		./expand/get_add_ex_value.c \

OBJCTS = ${SRC:.c=.o}

LDFLAGS = -L/goinfre/hait-hsa/homebrew/opt/readline/lib -lreadline
CPPFLAGS = -I/goinfre/hait-hsa/homebrew/opt/readline/include

make : 
	make -C ${LIBFT}

#  -fsanitize=address
CC = cc

all : ${OBJCTS}
	gcc  ${LDFLAGS} ${CPPFLAGS} ${SRC} ${LIB} -o ${NAME}

re : fclean all

clean:
	rm -f ${OBJCTS}

fclean: clean
	rm -rf *.o ${NAME}