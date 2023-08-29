/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:04:23 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list_env	*ft_lstnew_mod_e(char *content)
{
	t_list_env	*ls;
	char		*declare;
	char		*value;

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
		declare = ft_strjoin(declare, ls->value);
	ls->content = declare;
	ls->next = NULL;
	return (ls);
}

int	checker_export(char *str)
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
			break ;
	}
	return (1);
}

t_list_export	*ft_lstnew_mod_q_merge(char *content, char *ks)
{
	t_list_export	*ls;
	char			*declare;

	ls = malloc(sizeof(t_list_export));
	declare = malloc(sizeof(char *) * ft_strlen(content) + 13);
	declare = "declare -x ";
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

t_list_export	*ft_lstlast_export(t_list_export *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_export(t_list_export **lst, t_list_export *new)
{
	t_list_export	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast_export(*lst);
		last->next = new;
	}
}
