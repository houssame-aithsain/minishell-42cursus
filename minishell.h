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
void			readl_to_parse(char **env);
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