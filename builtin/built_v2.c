/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_v2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:54:14 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getvalue_env(char *content)
{
	t_get_v	gv;

	gv.i = 0;
	gv.j = 0;
	gv.value = "";
	while (content[gv.i])
	{
		if (content[gv.i] == '=' || (content[gv.i] == '+'
				&& content[gv.i + 1] == '='))
		{
			gv.j = gv.i;
			break ;
		}
		gv.i++;
	}
	if (gv.j == 0)
		return (content);
	if (gv.j > 0)
	{
		gv.temp = ft_substr(content, gv.j + 1, ft_strlen(content));
		gv.value = ft_strjoin_bb(gv.value, gv.temp);
		free(gv.temp);
	}
	return (gv.value);
}

void	ft_print_lst_env(t_list_env *ls)
{
	t_list_env	*la;

	la = ls;
	if (!la)
		return ;
	while (la)
	{
		if (ft_strncmp(la->content, "\t", 1) != 0)
			printf("%s\n", la->content);
		la = la->next;
	}
}

void	ft_second_delete_func_part_unset(t_list_env **curr, char *key)
{
	t_list_env	*current;
	t_list_env	*temp;

	current = *curr;
	temp = *curr;
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
			break ;
		}
		else
			current = current->next;
	}
}

void	ft_wrapped_free_for_delete_env_ee(t_list_env *temp)
{
	if (temp->key)
		free(temp->key);
	if (temp->value)
		free(temp->value);
	if (temp->content)
		free(temp->content);
	if (temp)
		free(temp);
}

void	ft_search_for_var_to_unset_ee(t_list_env **head, char *key)
{
	t_list_env	*temp;
	t_list_env	*current;

	current = *head;
	if (ft_strcmp((*head)->key, key) == 0)
	{
		temp = *head;
		*head = (*head)->next;
		ft_wrapped_free_for_delete_env_ee(temp);
	}
	else
	{
		while (current->next != NULL)
		{
			if (ft_strcmp(current->next->key, key) == 0)
			{
				temp = current->next;
				current->next = current->next->next;
				ft_wrapped_free_for_delete_env_ee(temp);
				break ;
			}
			else
				current = current->next;
		}
	}
}
