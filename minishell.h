#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include "./libft/libft.h"

#define TRUE 1
#define ECHO 2
#define GREP 1
#define ECHO_CHECK 0


typedef struct var
{
	int		j;
	int		i;
	int		index;
	int		pipe_count;
	int		copy_count;
	int		valid_quote;
	int		quote_type;
	int		if_quote;
	int		quote_count;
	char	*parsed_arr;
	char	quote_holder;
} t_var;

void	readl_to_parse();
int		if_grep(char *line, int i, int flag);
char	*parse_input(char *line, t_var *var);
int		ft_loop(char *line, t_var *var);
#endif