/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:34:31 by gothmane          #+#    #+#             */
/*   Updated: 2023/06/12 14:53:44 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_v_for_value(char *content, int j)
{
	char	*value;
	char	*tmp;
	
	tmp = NULL;
	value = ft_strdup("\"");
	if (j > 0)
	{
		tmp = ft_substr(content, j + 1, ft_strlen(content));
		value = ft_strjoin(value, tmp);
		free(tmp);
	}
	value = ft_strjoin(value, "\"");
	return (value);
}

char	*ft_getvalue(char *content)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	value = NULL;
	while (content[i])
	{
		if (content[i] == '=')
		{
			j = i;
			break;
		}
		i++;
	}
	if (j == 0)
		return (0);
	value = ft_get_v_for_value(content, j);
	return (value);
}

char	*ft_strnew_bb(size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}

char	*ft_strjoin_bb(char *s1, char const *s2)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = ft_strnew_bb(s1_len + s2_len);
	if (!new_str)
		return (NULL);
	i = -1;
	j = -1;
	while (++i < s1_len)
		*(new_str + i) = *(s1 + i);
	while (++j < s2_len)
		*(new_str + i++) = *(s2 + j);
	*(new_str + i) = '\0';
	return (new_str);
}

int	ft_detect_equal(char *key, char *content)
{
	int	i;

	i = 0;
	if (key)
	{
		i = ft_strlen(key);
		if ((content && content[i] == '=') || (content[i] == '+' && content[i + 1] == '=') )
			return (0);
	}
	return (1);
}

t_list_export *ft_lstnew_mod(char *content)
{
	t_list_export *ls;
	int i;
	char *key;
	char *value;
	char *declare;

	i = 0;
	ls = malloc(sizeof(t_list_export));
	declare = "declare -x ";
	key = ft_getkey(content);
	value = ft_getvalue(content);
	if (!ls)
		return (0);
	ls->key = key;
	ls->value = value;
	declare = ft_strjoin_bb(declare, ls->key);
	if (ft_detect_equal(ls->key, content) == 0)
		declare = ft_strjoin(declare, "=");
	if (ls->value)
		declare = ft_strjoin(declare, ls->value);
	ls->content = declare;
	ls->next = NULL;
	return (ls);
}


int	ft_exist_(const char *s1, char c)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	getlindex(const char *s1, const char *set)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (!ft_exist_(set, s1[i]))
			return (i);
		i++;
	}
	return (-1);
}

int	getrindex(const char *s1, const char *set)
{
	int	lengths1;

	lengths1 = ft_strlen(s1);
	while (lengths1 > 0)
	{
		if (!ft_exist_(set, s1[lengths1 - 1]))
			return (lengths1);
		lengths1--;
	}
	return (-1);
}

char	*ft_strtrim_exp_free(char *s1, char const *set)
{
	char	*trimmed;
	int		lcounter;
	int		rcounter;
	int		i;

	i = 0;
	if (!s1 || !set)
		return (0);
	lcounter = getlindex(s1, set);
	rcounter = getrindex(s1, set);
	trimmed = (char *) malloc(sizeof(char) * (rcounter - lcounter + 1));
	if (!trimmed)
		return (NULL);
	while (lcounter < rcounter)
	{
		trimmed[i] = s1[lcounter++];
		i++;
	}
	trimmed[i] = '\0';
	free(s1);
	return (trimmed);
}


t_list_env *ft_lstnew_mod_e(char *content)
{
	t_list_env	*ls;
	char		*declare;
	char		*value;
	char		*old_ls_v;
	
	declare = "";
	value = ft_getvalue(content);
	ls = malloc(sizeof(t_list_env));
	if (!ls)
		return (0);
	ls->key = ft_getkey(content);
	ls->value = ft_strtrim_exp_free(value, "\"");
	declare = ft_strjoin_bb(declare, ls->key);
	if (ft_detect_equal(ls->key, content) == 0)
		declare = ft_strjoin(declare, "=");
	if (ls->value)
	{
		old_ls_v = ls->value;
		declare = ft_strjoin(declare, old_ls_v);
		free(old_ls_v);
	}
	ls->content = declare;
	ls->next = NULL;
	return (ls);
}

int    checker_export(char *str)
{
   int	i;

   i = 0;
   while (str && str[i])
   {
		if (i == 0 && (!ft_isalpha(str[i]) && str[i] != '_'))
			return (0);
		else if ((ft_isdigit(str[i]) || ft_isalpha(str[i]) || str[i] == '_') 
			|| (str[i] == '+' && str[i + 1] == '='))
			i++;
		else
			return (0);
		if (str[i] == '=')
			break;
   }
   return (1);
}

t_list_export *ft_lstnew_mod_q_merge(char *content, char *ks)
{
	t_list_export *ls;
	int i;
	char *key;
	char *declare;

	i = 0;
	ls = malloc(sizeof(t_list_export));
	declare = malloc(sizeof(char *) * ft_strlen(content) + 13);
	declare = "declare -x ";
	key = NULL;
	if (!ls)
		return (0);
	ls->key = ks;
	ls->value = content;
	content = ft_strdup(ls->key);
	content = ft_strjoin(content, "=");
	content = ft_strjoin(content, ls->value);
	declare = ft_strjoin(declare, content);
	ls->content = declare;
	ls->next = NULL;
	return (ls);
}

t_list_export *ft_lstlast_export(t_list_export *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void ft_lstadd_back_export(t_list_export **lst, t_list_export *new)
{
	t_list_export *last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast_export(*lst);
		last->next = new;
	}
}

int ft_count_env_size(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int ft_isalpha_check(char c)
{
	if (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (0);
	return (1);
}

int ft_export_arg_checker(char *arg)
{
	int is_valid;
	int j;

	j = -1;
	is_valid = 1;
	if (arg[0] && ft_isalpha_check(arg[0]) == 0)
		is_valid = 0;
	return (is_valid);
}

int check_if_theres_equal(char *arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=' || (arg[i] == '+' && arg[i+1] == '='))
			return (0);
		i++;
	}
	return (1);
}

void ft_print_double_arr(char **var)
{
	int i;

	i = 0;
	while (var[i])
	{
		printf("[%s]\n", var[i]);
		i++;
	}
}

char *ft_getkey(char *content)
{
	int i;
	char *key;

	i = 0;
	key = NULL;
	while (content[i])
	{
		if (content[i] == '=' || content[i] == '+')
			break;
		i++;
	}
	key = ft_substr(content, 0, i);
	return (key);
}
char	*ft_get_v_for_value_for_qst(char *content, int j)
{
	char	*value;
	char	*tmp;
	
	tmp = NULL;
	value = ft_strdup("\"");
	if (j > 0)
	{
		tmp = ft_substr(content, j + 1, ft_strlen(content));
		value = ft_strjoin(value, tmp);
		free(tmp);
	}
	value = ft_strjoin(value, "\"");
	free(content);
	return (value);
}

char	*ft_getvalue_for_qst(char *content)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	value = NULL;
	while (content[i])
	{
		if (content[i] == '=')
		{
			j = i;
			break;
		}
		i++;
	}
	if (j == 0)
		return (0);
	value = ft_get_v_for_value_for_qst(content, j);
	return (value);
}

t_list_export *ft_lstnew_mod_for_qst(char *content)
{
	t_list_export *ls;
	int i;
	char *key;
	char *value;
	char *declare;

	i = 0;
	ls = malloc(sizeof(t_list_export));
	declare = "declare -x ";
	key = ft_getkey(content);
	value = ft_getvalue_for_qst(content);
	if (!ls)
		return (0);
	ls->key = key;
	ls->value = value;
	declare = ft_strjoin_bb(declare, ls->key);
	if (ft_detect_equal(ls->key, content) == 0)
		declare = ft_strjoin(declare, "=");
	if (ls->value)
		declare = ft_strjoin(declare, ls->value);
	ls->content = declare;
	ls->next = NULL;
	return (ls);
}


t_list_export *ft_create_export_lst(char **env)
{
    t_list_export	*node;
    t_list_export	*exp;
    int				i;

    i = 0;
    exp = NULL;
	node = ft_lstnew_mod("?=0");
   	ft_lstadd_back_export(&exp, node);
    while (env[i])
    {
        node = ft_lstnew_mod(env[i]);
        ft_lstadd_back_export(&exp, node);
        i++;
    }
    return (exp);
}

void ft_print_lst(t_list_export *la)
{
	int	i;

	i = 0;
	while (la)
	{
		if (la->key[0] == '?')
			la = la->next;
		else
		{
			while (la->content[i])
			{
				if ((i > (ft_strlen("declare -x ") + ft_strlen(la->key) + 1)
					&& i < (ft_strlen(la->content) - 1)) &&
					(la->content[i] == '"' || la->content[i] == '$'))
					printf("\\");
				printf("%c", la->content[i]);
				i++;
			}
			la = la->next;
			i = 0;
			printf("\n");
		}
	}
}

int	detect_equal(char *val, char *key)
{
	int	i;

	i = 0;
	while(val[i])
	{
		if (val[i] == key[i])
			i++;
		break;
	}
	if (val[i] == '=')
		return (1);
	return (0);
}

int check_clone_exp(t_list_export *exp, char *arg)
{
	t_list_export	*e;
	char			*temp_key;
	char			*temp_val;

	e = exp;
	temp_key = ft_getkey(arg);
	temp_val = ft_getvalue(arg);
	while (e)
	{
		if (ft_strcmp(e->key, temp_key) == 0)
		{
			free(temp_val);
			free(temp_key);
			if (e->value != NULL && temp_val == NULL)
					return (-2);
			else if (e->value == NULL && temp_val == NULL)
				return (-3);
			return (-1);
		}
		e = e->next;
	}
	free(temp_val);
	free(temp_key);
	return (1);
}

void ft_second_delete_func_part_export(t_list_export **curr, char *key)
{
    t_list_export *current = *curr;
    t_list_export *temp = *curr;
    while (current->next != NULL)
    {
        if (ft_strcmp(current->next->key, key) == 0)
        {
            temp = current->next;
            current->next = current->next->next;
            free(temp->content);
            free(temp->key);
			free(temp->value);
            free(temp);
            break;
        }
        else
            current = current->next;
    }
}
void ft_delete_node(t_list_export **head, char *key)
{
	t_list_export *temp;
	t_list_export *current;

	current = *head;
	if (ft_strcmp((*head)->key, key) == 0)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp->content);
		free(temp->value);
		free(temp->key);
		free(temp);
	}
	else
		ft_second_delete_func_part_export(head, key);
}

int	check_concat_var(t_list_export *exp, char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*get_val_for_a_specific_key(t_list_export *exp, char *key)
{
	t_list_export *e;

	e = exp;
	while (e && key)
	{
		if (ft_strcmp(e->key, key) == 0)
			return (e->value);
		e = e->next;
	}
	return (NULL);
}

t_list_env *ft_lstnew_mod_env_withplus(char *content, char *key)
{
    t_list_env	*ls;
	int			i;

	i = 0;
    ls = malloc(sizeof(t_list_env));
    if (!ls)
        return (0);
	ls->value = ft_getvalue_env(content);
   	content = ft_strdup(key);
	content = ft_strjoin_bb(content, ls->value);
	ls->content = content;
    ls->key = key;
    ls->next = NULL;
    return (ls);
}

void	__ft_first_handler_exp_v1(t_list_export **exp_lst, t_list_env **env_lst, char *arg)
{
	char		*key;
	t_list_env	*ss;
	
	key = NULL;
	ss = NULL;
	if (ft_export_arg_checker(arg) == 0)
	{
		if (check_if_theres_equal(arg) != 0)
		{
			key = ft_getkey(arg);
			ft_delete_node_env(env_lst, key);
			ft_lstadd_back_export(&(*exp_lst), ft_lstnew_mod(arg));
			free(key);
		}
		else
		{
			ss = ft_lstnew_mod_e(arg);
			ft_lstadd_back_export(&(*exp_lst), ft_lstnew_mod(arg));
			ft_lstadd_back_env(&(*env_lst), ss);
		}
	}
}

void	__ft_first_handler_exp_v2(t_list_export **exp_lst, t_list_env **env_lst, char *arg)
{
	char		*key;
	t_list_env	*ss;
	
	key = NULL;
	ss = NULL;
	key = ft_getkey(arg);
	ft_delete_node(exp_lst, key);
	ft_delete_node_env(env_lst, key);
	ft_lstadd_back_export(&(*exp_lst), ft_lstnew_mod(arg));
	ft_lstadd_back_env(&(*env_lst), ft_lstnew_mod_e(arg));
	free(key);
}

void	_check_exec_exp_wrapper(t_list_export **exp_lst, t_list_env **env_lst, char *arg)
{
	int	check;
	
	check = check_clone_exp(*exp_lst, arg);
	if (check != -1 && check != -2 && check != -3)
		__ft_first_handler_exp_v1(exp_lst, env_lst, arg);
	else if (check == -1)
		__ft_first_handler_exp_v2(exp_lst, env_lst, arg);
}

char **ft_export(t_list_export **exp_lst, char **arg, t_list_env **env_lst)
{
	char	**exported;
	int		ai;
	char	*sa;
	int		check;
	int		exp_c = -1;

	ai = -1;
	if (arg)
	{
		while (arg[++ai])
		{
			exp_c = checker_export(arg[ai]);
			if (exp_c == 0)
			{
				write(2, "minishell: not a valid identifier\n", ft_strlen("minishell: not a valid identifier\n"));
				exit_status = 1;
			}
			else
				_check_exec_exp_wrapper(exp_lst, env_lst, arg[ai]);
		}
	}
	return (exported);
}
