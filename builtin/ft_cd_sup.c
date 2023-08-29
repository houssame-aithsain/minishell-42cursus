/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_sup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:57:20 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	_ft_cd_sup_err(t_list_env **env_ls, t_list_export **exp_ls)
{
	(void)env_ls;
	write(2, "minishell: No such file or directory\n",
		ft_strlen("minishell: No such file or directory\n"));
	t_e.exit_status = 1;
	_ft_update_exit_status(exp_ls, t_e.exit_status);
}

void	ft_search_for_var_to_unset_export(t_list_export **head, char *key)
{
	t_list_export	*temp;
	t_list_export	*current;

	current = *head;
	if (ft_strcmp((*head)->key, key) == 0)
	{
		temp = *head;
		*head = (*head)->next;
		ft_wrapped_free_for_delete(temp);
	}
	else
	{
		while (current->next != NULL)
		{
			if (ft_strcmp(current->next->key, key) == 0)
			{
				temp = current->next;
				current->next = current->next->next;
				ft_wrapped_free_for_delete(temp);
				break ;
			}
			else
				current = current->next;
		}
	}
}

void	ft_unset(t_list_env **env, t_list_export **exp, char **var_to_unset)
{
	int				i;

	i = 0;
	while (var_to_unset[i] && ft_strcmp(var_to_unset[i], "?") != 0
		&& ft_strcmp(var_to_unset[i], "\t") != 0)
	{
		ft_search_for_var_to_unset_export(exp, var_to_unset[i]);
		ft_search_for_var_to_unset_ee(env, var_to_unset[i]);
		i++;
	}
}
