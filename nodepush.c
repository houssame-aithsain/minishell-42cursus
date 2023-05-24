/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodepush.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:49:57 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/05/23 20:18:22 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strlen_operatore(char *str)
{
	int i;
	int quote_numb;
	int quote_type;

	i = 0;
	quote_numb = 0;
	quote_type = 0;
	while (str && str[i])
	{
		if (str[i] == '"')
		{
			quote_type = '"';
			break;
		}
		if (str[i] == 39)
		{
			quote_type = 39;
			break;
		}
		i++;
	}
	i = 0;
	while (str && str[i])
	{
		if ((str[i] == '>' || str[i] == '<') && !(quote_numb % 2))
			break;
		if (str[i] == quote_type)
			quote_numb++;
		i++;
	}
	return i;
}

void n_remove(char *file)
{
	int space;

	space = 0;
	while (file && file[space])
	{
		if (file[space] == 11)
			file[space] = ' ';
		space++;
	}
}

int get_operatore(t_bash **dst, char *operatore, char *split, char *split_plus, int flag)
{
	int d_quote;
	int s_quote;
	int j;
	int i;

	i = 0;
	j = 0;
	d_quote = 0;
	s_quote = 0;
	if (split_plus && split_plus[ft_strlen(split_plus) - 1] == '|')
	{
		(*dst)->operator= '|';
		split_plus[ft_strlen(split_plus) - 1] = 0;
	}
	if (flag)
	{
		while (split && split[i] && operatore)
		{
			if (split[i] == '"')
				d_quote++;
			if (split[i] == 39)
				s_quote++;
			if (if_operatore(split + ft_strlen(split) - 1))
				j++;
			if (!ft_memcmp(operatore, split + i, ft_strlen(operatore)) && !(d_quote % 2) && !(s_quote % 2))
			{
				split[i] = 0;
				(*dst)->red_free++;
				(*dst)->redirection[(*dst)->flex] = malloc(sizeof(char) * ft_strlen(operatore) + 1);
				ft_strlcpy((*dst)->redirection[(*dst)->flex], operatore, ft_strlen(operatore) + 1);
				i++;
				if (split[i] == '>' || split[i] == '<')
					i++;
				if (split[i])
				{
					(*dst)->file_free++;
					(*dst)->file[(*dst)->flex] = malloc(sizeof(char) * ft_strlen(split + i) + 1);
					ft_strlcpy((*dst)->file[(*dst)->flex], split + i, ft_strlen_operatore(split + i) + 1);
					n_remove((*dst)->file[(*dst)->flex]);
					(*dst)->flex++;
					split = split + i + ft_strlen_operatore(split + i);
					if (if_operatore(split))
						get_operatore(dst, if_operatore(split), split, split_plus, flag);
					return 1;
				}
				else if (split_plus)
				{
					(*dst)->file_free++;
					(*dst)->file[(*dst)->flex] = malloc(sizeof(char) * ft_strlen(split_plus) + 1);
					ft_strlcpy((*dst)->file[(*dst)->flex], split_plus, ft_strlen_operatore(split_plus) + 1);
					n_remove((*dst)->file[(*dst)->flex]);
					split_plus[0] = 0;
					(*dst)->flex++;
					split_plus = split_plus + i + ft_strlen_operatore(split_plus + i);
					if (if_operatore(split_plus))
						get_operatore(dst, if_operatore(split_plus), split_plus, split_plus, flag);
					return (j + 2);
				}
				(*dst)->flex++;
				break;
			}
			i++;
		}
	}
	else
	{
		while (split && split[i] && operatore)
		{
			if (split[i] == '"')
				d_quote++;
			if (split[i] == 39)
				s_quote++;
			if (if_operatore(split + ft_strlen(split) - 1))
				j++;
			if (!ft_memcmp(operatore, split + i, ft_strlen(operatore)) && !(d_quote % 2) && !(s_quote % 2))
			{
				split[i] = 0;
				(*dst)->red_free++;
				(*dst)->redirection[(*dst)->flex] = malloc(sizeof(char) * ft_strlen(operatore) + 1);
				ft_strlcpy((*dst)->redirection[(*dst)->flex], operatore, ft_strlen(operatore) + 1);
				i++;
				if (split[i] == '>' || split[i] == '<')
					i++;
				if (split[i])
				{
					(*dst)->file_free++;
					(*dst)->file[(*dst)->flex] = malloc(sizeof(char) * ft_strlen(split + i) + 1);
					ft_strlcpy((*dst)->file[(*dst)->flex], split + i, ft_strlen_operatore(split + i) + 1);
					n_remove((*dst)->file[(*dst)->flex]);
					(*dst)->flex++;
					split = split + i + ft_strlen_operatore(split + i);
					if (if_operatore(split))
						get_operatore(dst, if_operatore(split), split, split_plus, flag);
					return 1;
				}
				else if (split_plus)
				{
					(*dst)->file_free++;
					(*dst)->file[(*dst)->flex] = malloc(sizeof(char) * ft_strlen(split_plus) + 1);
					ft_strlcpy((*dst)->file[(*dst)->flex], split_plus, ft_strlen_operatore(split_plus) + 1);
					n_remove((*dst)->file[(*dst)->flex]);
					(*dst)->flex++;
					split_plus = split_plus + i + ft_strlen_operatore(split_plus + i);
					if (if_operatore(split_plus))
						get_operatore(dst, if_operatore(split_plus), split_plus, NULL, flag);
					return (j + 2);
				}
				(*dst)->flex++;
				break;
			}
			i++;
		}
	}
	
	return 0;
}

int if_pipe(char *str, int flag)
{
	int i;

	i = 0;
	if (flag)
	{
		while(str && str[i])
		{
			if (str[i] == '|' && !str[i + 1])
				return 1;
			i++;
		}
		return 0;
	}
	while (str && str[i])
	{
		if (str[i++] != '|')
			return 1;
	}
	return 0;
}

void ft_strlcpy_shell(t_bash *dst, char *str)
{
	t_cp var;
	var.quote_numb = 0;
	var.quote_numb = 0;
	var.i = 0;
	var.j = 0;
	var.check = 0;
	var.space = 0;
	dst->red = 0;
	dst->flex = 0;
	dst->error = 0;
	dst->operator= 0;
	dst->file_free = 0;
	dst->red_free = 0;
	dst->redirection = NULL;
	dst->file = NULL;
	var.split = ft_split(str, ' ');
	while (var.split[var.i])
		var.i++;
	dst->arg = malloc(sizeof(char *) * (var.i + 1));
	// printf("dst->arg============{%p}\n", dst->arg);
	dst->args_malloc = var.i;
	var.i = 0;
	while (var.split && var.split[var.i])
	{
		var.j = 0;
		while (var.split[var.i][var.j])
		{
			if (var.split[var.i][var.j] == '>' || var.split[var.i][var.j] == '<')
				dst->red++;
			var.j++;
		}
		var.i++;
	}
	var.j = 0;
	dst->red++;
	dst->command = malloc(sizeof(char) * (ft_strlen(var.split[0]) + 1));
	dst->redirection = malloc(sizeof(char *) * dst->red);
	dst->file = malloc(sizeof(char *) * dst->red);
	// printf("dst->command========{%p}\n", dst->command);
	// printf("dst->redirection===={%p}\n", dst->redirection);
	// printf("dst->file==========={%p}\n", dst->file);
	var.i = 0;
	var.quote_type = quote_typ(var.split[var.i], '"', 39, 0);
	while (var.split && var.split[var.i] && var.split[var.i][var.j])
	{
		if (var.split[var.i][var.j] == var.quote_type)
			var.quote_numb++;
		if (var.split[var.i][var.j] == '|' && !(var.quote_numb % 2))
		{
			dst->operator= var.split[var.i][var.j];
			var.split[var.i][var.j] = 0;
			break;
		}
		dst->command[var.j] = var.split[var.i][var.j];
		var.j++;
	}
	dst->command[var.j] = 0;
	while (dst->command && dst->command[var.space])
	{
		if (dst->command[var.space] == 11)
			dst->command[var.space] = ' ';
		var.space++;
	}
	var.check = get_operatore(&dst, if_operatore(dst->command), dst->command, var.split[var.i + 1], 0);
	if (var.check >= 2)
		var.i++;
	var.j = 0;
	while (var.split && var.split[++var.i])
	{
		if (if_pipe(var.split[var.i], 1))
		{
			dst->operator= '|';
			var.split[var.i][ft_strlen(var.split[var.i]) - 1] = 0;
		}
		while (var.split && var.split[var.i] && if_operatore(var.split[var.i]))
		{
			var.check = get_operatore(&dst, if_operatore(var.split[var.i]), var.split[var.i], var.split[var.i + 1], 1);
			if (var.check == 2)
			{
				if (var.split[var.i] && var.split[var.i][0])
				{
					dst->arg[var.j] = malloc(sizeof(char) * ft_strlen(var.split[var.i]) + 1);
					ft_strlcpy(dst->arg[var.j], var.split[var.i], ft_strlen(var.split[var.i]) + 1);
					var.j++;
				}
				var.i++;
			}
			else if (var.check > 2)
			{
				if (var.split[var.i] && var.split[var.i][0])
				{
					dst->arg[var.j] = malloc(sizeof(char) * ft_strlen(var.split[var.i]) + 1);
					ft_strlcpy(dst->arg[var.j], var.split[var.i], ft_strlen(var.split[var.i]) + 1);
					var.j++;
				}
				var.i += 2;
			}
			else
				break;
			if (!var.split[var.i])
				break;
		}
		if (!var.split[var.i])
			break;
		if (var.split[var.i] && if_pipe(var.split[var.i], 0))
		{
			var.space = 0;
			dst->arg[var.j] = malloc(sizeof(char) * ft_strlen(var.split[var.i]) + 1);
			ft_strlcpy(dst->arg[var.j], var.split[var.i], ft_strlen(var.split[var.i]) + 1);
			if (dst->arg[var.j] && (dst->arg[var.j][ft_strlen(dst->arg[var.j]) - 1] == '|' || if_operatore(dst->arg[var.j])))
				dst->arg[var.j][ft_strlen(dst->arg[var.j]) - 1] = 0;
			while (dst->arg[var.j] && dst->arg[var.j][var.space])
			{
				if (dst->arg[var.j][var.space] == 11)
					dst->arg[var.j][var.space] = ' ';
				var.space++;
			}
			var.j++;
		}
		if (if_pipe(var.split[var.i], 1))
		{
			dst->operator= '|';
			var.split[var.i][ft_strlen(var.split[var.i]) - 1] = 0;
		}
	}
	var.i = 0;
	while(var.split[var.i])
		free(var.split[var.i++]);
	free(var.split[var.i++]);
	free(var.split);
	dst->redirection[dst->red_free] = NULL;
	dst->file[dst->file_free] = NULL;
	dst->arg[var.j] = NULL;
}

t_bash *get_last(t_bash *ptr)
{
	while (ptr->link)
		ptr = ptr->link;
	return (ptr);
}

t_bash *get_new(t_bash *new, char *str)
{
	new = malloc(sizeof(t_bash));
	new->command = malloc(sizeof(char) * ft_strlen(str));
	if (!new)
		return (0);
	new->link = NULL;
	return (new);
}

void newnode(t_bash **new, char *str)
{
	t_bash *current;
	t_bash *ptr;

	current = NULL;
	current = get_new(current, str);
	ft_strlcpy_shell(current, str);
	if (*new == NULL)
	{
		*new = current;
		return;
	}
	ptr = get_last(*new);
	ptr->link = current;
}

void nodepush(t_bash **head, char *result, int lent)
{
	int i;

	i = 0;
	while (i < lent)
	{
		newnode(head, result);
		i++;
	}
}
