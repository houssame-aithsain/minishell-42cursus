#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include "./libft/libft.h"
#include <fcntl.h>

#define TRUE		1
#define D_QUOTE		2
#define S_QUOTE		1
#define PIPE		3
#define BACK_SLASH	4
#define SEMICOLON	5
#define S_ERROR		6
#define RD_ERROR	7
#define S_RD_ERROR	8
#define NSFOD		9
// str open
typedef struct s_node{
	int		red;
	int		flex;
	int		file_free;
	int		red_free;
	int		args_malloc;
	char	**file;
	char	**redirection;
	char	**arg;
	char	*command;
	char	*operatore;
	char	operator;
	int		error;
	struct s_node *link;
} t_bash;

typedef struct format{
	char *holder;
	int error;
	int qoute_numb;
	int dqoute_numb;
	int o_count;
	int i;
	int j;
} t_format;

typedef struct rquotes{
	int v;
	int j;
	int i;
	int arg_count;
	int s_qoute;
	int d_qoute;
	char *command;
	char **arg;
	char *file;
	char qoute_type;
} t_rquotes;

typedef struct cp{
	char quote_type;
	int	 quote_numb;
	int remove;
	int check;
	int space;
	int j;
	int i;
	char **split;
} t_cp;

// str close
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

typedef struct s_list_export
{
	char					*content;
	char					*key;
	char					*value;
	struct s_list_export	*next;
}			t_list_export;

typedef struct s_list_env
{
	char					*content;
	char					*key;
	char					*value;
	struct s_list_env		*next;
}			t_list_env;

char			quote_typ(char *ncoom, char f_type, char s_type);
char			*get_val_for_a_specific_key(t_list_export *exp, char *key);
void			get_value_from_variable(t_list_export *exp_list, t_bash **ptr);
char			*ft_strnew_bb(size_t size);
char			*ft_strjoin_bb(char *s1, char const *s2);
char			*if_operatore(char *ncoom);
void			readl_to_parse(char **env);
int				if_grep(char *line, int i, int flag);
char			*parse_input(char *line, t_var *var);
int				ft_loop(char *line, t_var *var);
void			nodepush(t_bash **head, char *result, int lent);
char 			**ft_export(t_list_export **exp_lst, char **arg, t_list_env **env_lst);
t_list_export	*ft_create_export_lst(char **env);
t_list_export	*ft_lstnew_mod(char *content);
char			*ft_getkey(char *content);
void			ft_print_lst(t_list_export *ls);
void			ft_echo(char **str);
void			ft_cd(char *path);
int 			ft_pwd(void);
int 			ft_count_2d(char **two_dem);
void			ft_unset(t_list_env **env, t_list_export **exp, char *var_to_unset);
void    		ft_env(char **env);
void    		ft_exit(void);
void			ft_print_double_arr(char **var);
void			ft_print_lst_env(t_list_env *ls);
t_list_env		*put_env_to_ls(char **env);
t_list_env 		*ft_lstlast_env(t_list_env *lst);
void 			ft_lstadd_back_env(t_list_env **lst, t_list_env *new);
t_list_env 		*ft_lstnew_mod_env(char *content);
void 			ft_delete_node_env(t_list_env **head, char *key);
char			*ft_getvalue_env(char *content);
int				ft_detect_equal(char *key, char *content);
void 			ft_delete_node(t_list_export **head, char *key);
int    			checker_export(char *str);
void 			ft_search_for_var_to_unset_export(t_list_export **head, char *key);
char			**ft_getpath_cmd(t_list_env *env);
char			*ft_check_access_cmd(t_bash *cmd, t_list_env *env);
char			**ft_final_exec_sgl_cmd(t_bash *cmd, t_list_env *env);
void			ft_piping_bash(t_bash *cmd, t_list_env *env);
char			**ft_lst_to_array(t_list_env *env);
int				ft_lstsize_env(t_list_env *lst);
int				ft_count_cmds(t_bash *cmd);
char			*ft_check_access_cmd(t_bash *cmd, t_list_env *env);
void			ft_free_args(char **arg);
char			**ft_getpath_cmd(t_list_env *env);
int				*ft_open_files(t_bash *cmd);
int				ft_file_counter_redir(t_bash *cmd);
void			ft_redir_ex(t_bash *cmd, t_list_env *env);
#endif