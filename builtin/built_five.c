/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_five.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:59:07 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list_env	*ft_lstlast_env(t_list_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_env(t_list_env **lst, t_list_env *new)
{
	t_list_env	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast_env(*lst);
		last->next = new;
	}
}

t_list_env	*put_env_to_ls(char **env)
{
	t_list_env	*node;
	t_list_env	*env_ls;
	int			i;

	i = 0;
	env_ls = NULL;
	while (env[i])
	{
		node = ft_lstnew_mod_env(env[i]);
		ft_lstadd_back_env(&env_ls, node);
		i++;
	}
	node = ft_lstnew_mod_env(ft_strdup("\t"));
	ft_lstadd_back_env(&env_ls, node);
	return (env_ls);
}
