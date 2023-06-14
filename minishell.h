#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include "./libft/libft.h"
#include <fcntl.h>
#include <readline/history.h>

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
#define AR			10

int rl_catch_signals;
int	exit_status;
int r;

typedef struct s_op{
	int		i;
	char	q_type;
	int		q_numb;
	int		skipe;
} t_op;

typedef struct expande{
	int		error;
	char	*value;
	int		va_l;
	int		arg_i;
	char	*rt_value;
	int		is_heredoc;
	char	*s_key;
	char	q_type;
	int		vl_i;
	int		mlc;
	size_t	lent;
	int		i;
	int		switcher;
	int		len;
	size_t	cmd_len;
	char	*holder;
	char	**key;
	int		d_q;
} t_ex;

typedef struct s_node{
	int		d_q;
	int		s_q;
	int		j;
	int		i;
	int		expande;
	int		rd_count;
	int		flex;
	int		file_free;
	int		red_free;
	char	**file;
	char	**redirection;
	char	**arg;
	char	*command;
	char	op;
	int		error;
	int		in;
	int		out;
	int		fd_heredoc;
	int		h_expn;
	struct s_node *link;
} t_bash;

typedef struct format{
	char	*container;
	int		error;
	int		q_cnt;
	int		dq_cnt;
	int		o_count;
	char	*arr;
	char	*value;
	int		in;
	int		vl_c;
	int		len;
	int		i;
	int		j;
} t_format;

typedef struct rquotes{
	int		k_c;
	int		l_s;
	int		cmd_c;
	int		arg_c;
	int		count;
	int		arg_count;
	int		s_qoute;
	int		d_qoute;
	char	*command;
	char	**arg;
	char	**file;
	char	qoute_type;
	int		*c_c;
	int		*a_c;
	char	*cmd;
	int		quote_numb;
} t_rquotes;

typedef struct cp{
	char	quote_type;
	int		q_count;
	int		remove;
	int		check;
	int		space;
	int		j;
	int		i;
	int		splt;
	char	**split;
} t_cp;

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

typedef struct s_heredoc_data
{
	int		counter;
	char	*data_hd;
	char	*arr;
	char	*eof;
}			t_heredoc_data;

void			ft_check_ambg(t_ex *expn);
int				get_value_lent(char **key, t_list_export *exp_list, t_ex *expn);
t_ex			*get_add_expanded_value(char *arg, t_ex *expn, t_list_export *exp_list);
char			q_t(char c);
char			*ft_rewrite(char *holder);
int				if_expnd(char *holder, t_ex **expn);
char			**ft_split_e(char const *s);
int				if_valide_f(t_bash *tmp, t_rquotes *var, t_ex *ex);
int				if_ambiguous(char *arg, int i);
void			handler(int sig_t);
void			_f_vars_reset_(t_rquotes *var);
void			_files_q_rm(t_bash *tmp, t_bash **ptr, t_rquotes *var, t_ex *ex);
int				if_valide_c(t_bash *tmp, t_rquotes *var, t_ex *ex);
int				if_valide_a(t_bash *tmp, t_rquotes *var, t_ex *ex);
void			_args_q_rm(t_bash *tmp, t_bash **ptr, t_rquotes *var, t_ex *ex);
int				__if_cmd(t_bash *tmp, t_bash **ptr, t_rquotes *var, t_ex *ex);
void			_s_q_c(t_bash **ptr, t_bash *tmp,t_rquotes *var);
void			_q_vars_reset_(t_rquotes *var);
int				rm_args_empty_vars(t_bash *tmp, t_bash **ptr, t_rquotes *var, t_ex *ex);
int				rm_cmd_empty_vars(t_bash *tmp, t_bash **ptr, t_rquotes *var, t_ex *ex);
void			ft_free_q(t_bash *tmp, t_rquotes *var);
void			qoutes_counter(char *arg, int *s_qoute, int *d_qoute);
void			str_cp(char *dst, t_rquotes *var, int flag, t_bash **ptr);
void			quote_sanitizer(t_bash **ptr, t_ex *ex);
int				get_s_rd(t_bash **dst, char *operatore, char *split, char *split_plus);
void			_pipe_checker(t_cp *var, t_bash *dst);
void			ft_free(t_cp *var, t_bash *dst);
void			_vars_reset(t_cp *var, t_bash *dst);
void			get_parse(t_bash *dst, char *str);
int				if_pipe(char *str, int flag);
void			n_remove(char *file);
int				get_operator_length(char *str);
char			*if_operator(char *ncoom);
void			list_builder(t_bash **head, char *result, int lent);
void			check_str_errors(char *tmp, int *error);
char			*spaces_trim(char *str);
int				arg_lent(char **arg);
void			extract_q_segments(t_format *var, t_ex *expn);
void			quotes_remover(t_bash **ptr, t_ex *ex);
void			check_str_errors(char *tmp, int *error);
void			quotes_rewriter(t_bash **ptr);
void			heredoc_cmd_finder(t_bash **ptr);
char			*spaces_trim(char *str);
void			list_parse(char *str, t_bash **ptr, t_list_env **env_list, t_list_export **exp_list);
int				rd_check(char *str, int i);
char			*ft_get_value(char *arg, t_ex *expn,t_list_export *exp_list);
int				check_if_var(char *str, char quote_type);
int				if_expn(char *str, t_ex *expn, t_list_export *exp_list);
int 			is_n_heredoc(char *str, int i);
char			*ft_key_dup(char *str);
int				if_valide(char *str, int i);
t_ex			*_q_r_change(t_ex *expn);
int				get_key(char *arg, char **str);
t_ex			*key_dup_routine(t_ex *expn);
int				get_keys_lent(char *str);
int				print_error(t_bash *ptr);
char			quote_t(char *ncoom, char f_type, char s_type, int flag);
char			*get_val_for_a_specific_key(t_list_export *exp, char *key);
t_ex			*get_expand_vars(t_list_export *exp_list, char *holder);
int				print_error(t_bash *ptr);
char			quote_t(char *ncoom, char f_type, char s_type, int flag);
char			*get_val_for_a_specific_key(t_list_export *exp, char *key);
t_ex			*get_expand_entry(t_list_export *exp_list, char *holder);
char			*ft_strnew_bb(size_t size);
char			*ft_strjoin_bb(char *s1, char const *s2);
char			*if_operator(char *ncoom);
void			readl_to_parse(char **env);
char			*parse_input(char *line, t_var *var);
int				ft_loop(char *line, t_var *var);
char 			**ft_export(t_list_export **exp_lst, char **arg, t_list_env **env_lst);
t_list_export	*ft_create_export_lst(char **env);
t_list_export	*ft_lstnew_mod(char *content);
char			*ft_getkey(char *content);
void			ft_print_lst(t_list_export *ls);
void			ft_echo(char **str);
void			ft_cd(char *path, t_list_env **env_ls);
int 			ft_pwd(void);
int 			ft_count_2d(char **two_dem);
void			ft_unset(t_list_env **env, t_list_export **exp, char **var_to_unset);
void    		ft_env(char **env);
void    		ft_exit(t_bash *ptr);
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
int				ft_open_files(t_bash *cmd);
int				ft_file_counter_redir(t_bash *cmd);
void			ft_redir_ex(t_bash *cmd, t_list_env *env);
int				ft_infile_redir(t_bash *cmd, t_list_env *env);
void			ft_run_redir(t_bash *cmd, t_list_env *env, t_list_export *exp);
int				ft_final_exec_sgl_cmd_without_fork(t_bash *cmd, t_list_env **env, t_list_export **exp);
char			*ft_heredoc(t_bash *cmd, t_list_export *exp);
void 			n_pipe(t_bash *cmd, t_list_env **env, t_list_export **exp_ls);
int				ft_count_cmds_exp(t_bash *cmd);
int				ft_check_builtins(t_bash *ptr, t_list_env **env_ls, t_list_export **exp_ls);
int				_ft_check_if_redir(t_bash *cmd);
char			*ft_heredoc_v2(t_bash *cmd);
int				__ft_check_heredoc(t_bash *cmd, t_list_export *exp);
int				ft_check_slash_dot(t_bash *cmd, t_list_env *env);
int				_ft_check_builtin_return_int(t_bash *ptr);
int				_ft_check_builtin_return_int_v2(t_bash *ptr);
char			*ft_expand_in_heredoc(char *arg, t_list_export *exp);
void			ft_lstadd_back_export(t_list_export **lst, t_list_export *new);
int				ft_heredocs_counter(char **redir);

#endif