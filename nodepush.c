/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodepush.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:49:57 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/05/08 18:12:39 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strlcpy_shell(t_list *dst, char *str)
{
	int j;
	int i;
	char **split;

	// printf("str => %s\n", str);
	i = 0;
	j = 0;
	dst->operator = 0;
	split = ft_split(str, ' ');
	while(split[i])
		i++;
	dst->arg = malloc(sizeof(char *) * i + 1);
	i = 0;
	while(split && split[i] && split[i][j])
	{
		dst->command[j] = split[i][j];
		j++;
		if (split[i][j] == '|')
		{
			dst->operator = split[i][j];
			break;
		}
	}
	dst->command[j] = 0;
	j = 0;
	while(split && split[++i])
	{
		if (split[i][ft_strlen(split[i]) - 1] == '|')
			dst->operator = split[i][ft_strlen(split[i]) - 1];
		else
		{
			dst->arg[j] = malloc(sizeof(char) * ft_strlen(split[i]));
			ft_strlcpy(dst->arg[j], split[i], ft_strlen(split[i]) + 1);
			j++;	
		}
	}
	dst->arg[j] = NULL;
}

t_list	*get_last(t_list *ptr)
{
	while (ptr->link)
		ptr = ptr->link;
	return (ptr);
}

t_list	*get_new(t_list *new, char *str)
{
	new = malloc(sizeof(t_list));
	new->command = malloc(sizeof(char) * ft_strlen(str));
	if (!new)
		return (0);
	new->link = NULL;
	return (new);
}

void	newnode(t_list **new, char *str)
{
	t_list	*current;
	t_list	*ptr;

	current = NULL;
	current = get_new(current, str);
	ft_strlcpy_shell(current , str);
	if (*new == NULL)
	{
		*new = current;
		return ;
	}
	ptr = get_last(*new);
	ptr->link = current;
}

void	nodepush(t_list **head, char *result, int lent)
{
	int i;

	i = 0;
	while(i < lent)
	{
		newnode(head, result);
		i++;
	}
}
