/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 02:16:50 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/11 13:40:12 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bash	*get_last(t_bash *ptr)
{
	while (ptr->link)
		ptr = ptr->link;
	return (ptr);
}

t_bash	*get_new_node(t_bash *new, char *str)
{
	new = malloc(sizeof(t_bash));
	if (!new)
		return (0);
	new->link = NULL;
	return (new);
}

void	newnode(t_bash **new, char *str)
{
	t_bash	*current;
	t_bash	*ptr;

	current = NULL;
	current = get_new_node(current, str);
	get_parse(current, str);
	if (*new == NULL)
	{
		*new = current;
		return ;
	}
	ptr = get_last(*new);
	ptr->link = current;
}

void	list_builder(t_bash **head, char *result, int lent)
{
	int	i;

	i = 0;
	while (i < lent)
	{
		newnode(head, result);
		i++;
	}
}
