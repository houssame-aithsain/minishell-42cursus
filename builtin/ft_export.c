/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:34:31 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list_env	*ft_lstnew_mod_env_withplus(char *content, char *key)
{
	t_list_env	*ls;

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

void	__ft_first_handler_exp_v1(t_list_export **exp_lst, t_list_env **env_lst,
		char *arg)
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

void	__ft_first_handler_exp_v2(t_list_export **exp_lst, t_list_env **env_lst,
		char *arg)
{
	char		*key;

	key = NULL;
	key = ft_getkey(arg);
	ft_delete_node(exp_lst, key);
	ft_delete_node_env(env_lst, key);
	ft_lstadd_back_export(&(*exp_lst), ft_lstnew_mod(arg));
	ft_lstadd_back_env(&(*env_lst), ft_lstnew_mod_e(arg));
	free(key);
}

void	_check_exec_exp_wrapper(t_list_export **exp_lst, t_list_env **env_lst,
		char *arg)
{
	int	check;

	check = check_clone_exp(*exp_lst, arg);
	if (check != -1 && check != -2 && check != -3)
		__ft_first_handler_exp_v1(exp_lst, env_lst, arg);
	else if (check == -1)
		__ft_first_handler_exp_v2(exp_lst, env_lst, arg);
}

char	**ft_export(t_list_export **exp_lst, char **arg, t_list_env **env_lst)
{
	int		ai;
	int		exp_c;

	exp_c = -1;
	ai = -1;
	if (arg)
	{
		while (arg[++ai])
		{
			exp_c = checker_export(arg[ai]);
			if (exp_c == 0)
			{
				write(2, "minishell: not a valid identifier\n",
					ft_strlen("minishell: not a valid identifier\n"));
				t_e.exit_status = 1;
			}
			else
				_check_exec_exp_wrapper(exp_lst, env_lst, arg[ai]);
		}
	}
	return (NULL);
}
