# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/04 23:30:28 by hait-hsa          #+#    #+#              #
#    Updated: 2023/06/15 18:50:53 by hait-hsa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

LIBFT		=	libft/libft.a

CC			=	cc

RM			=	rm -rf

CFLAGS		=	-Wall -Wextra -Werror

SRCS		=	./signales/c_d_sig.c ./parsing/if_operator.c ./parsing/errors_checker.c \
		./parsing/quotes_sanitizing/cmd_unquote.c ./parsing/quotes_sanitizing/files_unquote.c \
		./parsing/quotes_sanitizing/args_unquote.c ./parsing/quotes_sanitizing/cmd_utils.c \
		./parsing/quotes_sanitizing/args_utils.c ./parsing/utils.c ./parsing/utils2.c \
		./parsing/get_s_rd.c ./parsing/get_parse.c ./parsing/utils1.c \
		./parsing/get_s_node_args_ready.c print_error.c ./expand/get_expand_vars.c \
		./expand/keys_dup.c ./expand/utils.c minishell.c readl_and_exec.c \
		./parsing/list_builder.c ./builtin/ft_export.c ./builtin/builtins_func.c \
		./exec/sglcmd.c ./pipe/pipe.c  ./redir/redirv2.c ./redir/heredoc.c \
		./parsing/quotes_sanitizing/files_utils.c ./parsing/quotes_sanitizing/str_cp.c \
		./parsing/heredoc_cmd_finder.c ./parsing/ft_split_e.c ./expand/utils1.c ./expand/utils2.c \
		./expand/get_add_ex_value.c ./builtin/built_main.c  ./builtin/built_v2.c  ./builtin/built_four.c ./builtin/built_five.c ./builtin/built_three.c\
		./builtin/exp1.c ./builtin/exp2.c ./builtin/exp3.c ./builtin/exp4.c ./builtin/exp5.c ./builtin/exp6.c ./builtin/exp7.c\
		./pipe/pipe1.c ./pipe/pipe2.c ./pipe/pipe3.c ./pipe/pipe4.c ./pipe/pipe5.c\
		./redir/h_utils.c ./redir/h_utils1.c ./redir/rd_utils.c ./redir/rd_utils1.c \
        ./redir/ft_check_access.c ./redir/ft_h_hd.c ./builtin/ft_cd_sup.c ./redir/ft_run_redir.c \
		./utils.c \

LDFLAGS		= -L/goinfre/hait-hsa/homebrew/opt/readline/lib -lreadline
CPPFLAGS	= -I/goinfre/hait-hsa/homebrew/opt/readline/include

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(LIBFT) 
				$(CC) $(OBJS) $(LIBFT) -o $(NAME) ${LDFLAGS} ${CPPFLAGS}
$(LIBFT)	:
				make -C ./libft

clean		:
				${RM} $(OBJS)
				make clean -C ./libft

fclean		:	clean
				${RM} $(NAME)
				make fclean -C ./libft

re			:	fclean all

.PHONY		:	all clean fclean re