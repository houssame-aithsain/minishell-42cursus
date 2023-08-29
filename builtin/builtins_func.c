/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 22:09:30 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_second_delete_func_part(t_list_env **curr, char *key)
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

void	ft_wrapped_free_for_delete(t_list_export *temp)
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

int	ft_check_minus_n_(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (i == 0 && str[i] == '-')
			j++;
		if (str[i] == 'n')
			j++;
		i++;
	}
	if (i == j && i != 0)
		return (1);
	return (0);
}

int	ft_count_2d(char **two_dem)
{
	int	i;

	i = 0;
	while (two_dem[i])
		i++;
	return (i);
}

t_list_env	*ft_lstnew_mod_env(char *content)
{
	t_list_env	*ls;
	char		*declare;

	ls = malloc(sizeof(t_list_env));
	declare = "";
	if (!ls)
		return (0);
	ls->key = ft_getkey(content);
	ls->value = ft_getvalue_env(content);
	declare = ft_strjoin_bb(declare, ls->key);
	if (ft_detect_equal(ls->key, content) == 0)
		declare = ft_strjoin(declare, "=");
	if (ls->value)
		declare = ft_strjoin(declare, ls->value);
	ls->content = declare;
	ls->next = NULL;
	return (ls);
}
