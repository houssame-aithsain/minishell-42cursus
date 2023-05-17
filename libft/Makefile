SRCS	= ft_striteri.c\
		ft_strtrim.c \
		ft_substr.c \
		ft_memcmp.c \
		ft_strcmp.c \
		ft_strrchr.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_memcpy.c \
		ft_memmove.c  \
		ft_strlen.c  \
		ft_strnstr.c  \
		ft_strncmp.c  \
		ft_strlcat.c  \
		ft_isalnum.c  \
		ft_strchr.c  \
		ft_memset.c  \
		ft_bzero.c  \
		ft_atoi.c   \
		ft_isalpha.c  \
		ft_isascii.c  \
		ft_memchr.c  \
		ft_strlcat.c  \
		ft_strlcpy.c  \
		ft_calloc.c  \
		ft_strdup.c   \
		ft_strlcat.c  \
		ft_strjoin.c  \
		ft_split.c  \
		ft_putchar_fd.c  \
		ft_putstr_fd.c \
		ft_putnbr_fd.c \
		ft_putendl_fd.c \
		ft_strmapi.c\
		ft_itoa.c \

SRCS_BONUS = ft_lstnew.c\
			ft_lstadd_front.c\
			ft_lstnew.c\
			ft_lstsize.c\
			ft_lstlast.c\
			ft_lstadd_back.c\
			ft_lstdelone.c\
			ft_lstclear.c\
			ft_lstiter.c\
			ft_lstmap.c\

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

OBJS = ${SRCS:.c=.o}

OBJS_BONUS = ${SRCS_BONUS:.c=.o}

RM = rm -f

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}


${NAME}: ${OBJS}
		ar rcs ${NAME} ${OBJS}

all : 	${NAME}

clean:
		${RM} *.o

fclean: clean
		${RM} ${NAME}

re:	fclean all

bonus:	${NAME} ${OBJS_BONUS}
		ar rcs ${NAME} ${OBJS_BONUS}
