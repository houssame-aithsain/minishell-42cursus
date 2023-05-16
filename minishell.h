#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include "./libft/libft.h"

#define TRUE		1
#define D_QUOTE		2
#define S_QUOTE		1
#define PIPE		3
#define BACK_SLASH	4
#define SEMICOLON	5
#define S_ERROR		6
#define NSFOD		9

typedef struct s_node{
	int		flex;
	char	**file;
	char	**redirection;
	char	*command;
	char	**arg;
	char	operator;
	int		error;
	struct s_node *link;
} t_bash;

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

char	*if_operatore(char *ncoom);
void	readl_to_parse();
int		if_grep(char *line, int i, int flag);
char	*parse_input(char *line, t_var *var);
int		ft_loop(char *line, t_var *var);
void	nodepush(t_bash **head, char *result, int lent);
#endif