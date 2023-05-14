/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodepush.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:49:57 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/05/14 21:51:50 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_operatore(t_list **dst, char *operatore, char *split, char *split_plus, int flag)
{
	int j;
	int	i;

	i = 0;
	j = 0;
	if (flag)
	{
		while(split && split[i] && operatore)
	{
		if (if_operatore(split + ft_strlen(split) - 3))
			j++;
		if (!ft_memcmp(operatore, split + i, ft_strlen(operatore)))
		{
			split[i] = 0;
			(*dst)->redirection = malloc(sizeof(char) * ft_strlen(operatore) + 1);
			ft_strlcpy((*dst)->redirection, operatore, ft_strlen(operatore) + 1);
			i++;
			if (split[i] == '>' || split[i] == '<')
				i++;
			if (split[i])
			{
				(*dst)->file = malloc(sizeof(char) * ft_strlen(split + i) + 1);
				ft_strlcpy((*dst)->file, split + i, ft_strlen(split + i) + 1);
				return 1;
			}
			else if (split_plus)
			{
				(*dst)->file = malloc(sizeof(char) * ft_strlen(split_plus) + 1);
				ft_strlcpy((*dst)->file, split_plus, ft_strlen(split_plus) + 1);
				return (j + 2);
			}
			break;
		}
		i++;
	}	
	}
	else
	{
		while(split && split[i] && operatore)
		{
			if (!ft_memcmp(operatore, split + i, ft_strlen(operatore)))
			{
				split[i] = 0;
				(*dst)->redirection = malloc(sizeof(char) * ft_strlen(operatore) + 1);
				ft_strlcpy((*dst)->redirection, operatore, ft_strlen(operatore) + 1);
				i++;
				if (split[i] == '>' || split[i] == '<')
					i++;
				if (split[i])
				{
					(*dst)->file = malloc(sizeof(char) * ft_strlen(split + i) + 1);
					ft_strlcpy((*dst)->file, split + i, ft_strlen(split + i) + 1);
					return 1;
				}
				break;
			}
			i++;
		}	
	}
	return 0;
}

int	if_pipe(char *str)
{
	int i;

	i = 0;
	while(str && str[i])
	{
		if (str[i++] != '|')
			return 1;
	}
	return 0;
}

void	ft_strlcpy_shell(t_list *dst, char *str)
{
	int check;
	int space;
	int j;
	int i;
	char **split;

	// printf("\n\n%s\n\n",str);
	i = 0;
	j = 0;
	check = 0;
	space = 0;
	dst->error = 0;
	dst->operator = 0;
	dst->redirection = NULL;
	dst->file = NULL;
		split = ft_split(str, ' ');
	while(split[i])
		i++;
	dst->arg = malloc(sizeof(char *) * i);
	i = 0;
	while(split && split[i] && split[i][j])
	{
		dst->command[j] = split[i][j];
		j++;
		if (split[i][j] == '|')
		{
			dst->operator = split[i][j];
			split[i][j] = 0;
			break;
		}
	}
	while(dst->command && dst->command[space])
	{
		if (dst->command[space] == '~')
			dst->command[space] = ' ';
		space++;
	}
	dst->command[j] = 0;
	get_operatore(&dst, if_operatore(dst->command), dst->command, NULL, 0);
	j = 0;
	while(split && split[++i])
	{
		if (split[i][ft_strlen(split[i]) - 1] == '|')
		{
			dst->operator = split[i][ft_strlen(split[i]) - 1];
			split[i][ft_strlen(split[i]) - 1] = 0;
		}
		if (if_operatore(split[i]))
		{
			check = get_operatore(&dst, if_operatore(split[i]), split[i], split[i + 1], 1);
			if (check == 2)
				i++;
			else if (check == 3)
				i += 2;
		}
		if (split[i] && if_pipe(split[i]))
		{
			space = 0;
			dst->arg[j] = malloc(sizeof(char) * ft_strlen(split[i]) + 1);
			ft_strlcpy(dst->arg[j], split[i], ft_strlen(split[i]) + 1);
			if (dst->arg[j] && (dst->arg[j][ft_strlen(dst->arg[j]) - 1] == '|' || if_operatore(dst->arg[j])))
				dst->arg[j][ft_strlen(dst->arg[j]) - 1] = 0;
			while(dst->arg[j] && dst->arg[j][space])
			{
				if (dst->arg[j][space] == '~')
					dst->arg[j][space] = ' ';
				space++;
			}
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
