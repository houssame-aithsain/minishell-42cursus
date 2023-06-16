/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:06:13 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_clone_exp(t_list_export *exp, char *arg)
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

void	ft_second_delete_func_part_export(t_list_export **curr, char *key)
{
	t_list_export	*current;
	t_list_export	*temp;

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

void	ft_delete_node(t_list_export **head, char *key)
{
	t_list_export	*temp;
	t_list_export	*current;

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
	(void)exp;
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
	t_list_export	*e;

	e = exp;
	while (e && key)
	{
		if (ft_strcmp(e->key, key) == 0)
			return (e->value);
		e = e->next;
	}
	return (NULL);
}
