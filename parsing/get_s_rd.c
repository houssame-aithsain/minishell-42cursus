/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_s_rd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 04:57:22 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/14 10:49:17 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	_main_rd_finder_(t_bash **dst, char *split, char *split_plus)
{
	(*dst)->file_free++;
	(*dst)->file[(*dst)->flex] = malloc(sizeof(char) * ft_strlen(split
				+ (*dst)->i) + 1);
	ft_strlcpy((*dst)->file[(*dst)->flex], split + (*dst)->i,
		get_operator_length(split + (*dst)->i) + 1);
	n_remove((*dst)->file[(*dst)->flex]);
	(*dst)->flex++;
	split = split + (*dst)->i + get_operator_length(split + (*dst)->i);
	if (if_operator(split))
		get_s_rd(dst, if_operator(split), split, split_plus);
}

void	_side_rd_finder_(t_bash **dst, char *split, char *split_plus)
{
	(*dst)->file_free++;
	(*dst)->file[(*dst)->flex] = malloc(sizeof(char) * ft_strlen(split_plus)
			+ 1);
	ft_strlcpy((*dst)->file[(*dst)->flex], split_plus,
		get_operator_length(split_plus) + 1);
	n_remove((*dst)->file[(*dst)->flex]);
	split_plus[0] = 0;
	(*dst)->flex++;
	split_plus = split_plus + (*dst)->i + get_operator_length(split_plus
			+ (*dst)->i);
	if (if_operator(split_plus))
		get_s_rd(dst, if_operator(split_plus), split_plus, NULL);
}

int	rd_dup_routine(t_bash **dst, char *split, char *split_plus, char *op)
{
	if (!ft_memcmp(op, split + (*dst)->i, ft_strlen(op)) && !((*dst)->d_q % 2)
		&& !((*dst)->s_q % 2))
	{
		split[(*dst)->i] = 0;
		(*dst)->red_free++;
		(*dst)->redirection[(*dst)->flex] = malloc(sizeof(char) * ft_strlen(op)
				+ 1);
		ft_strlcpy((*dst)->redirection[(*dst)->flex], op, ft_strlen(op) + 1);
		(*dst)->i++;
		if (split[(*dst)->i] == '>' || split[(*dst)->i] == '<')
			(*dst)->i++;
		if (split[(*dst)->i])
		{
			_main_rd_finder_(dst, split, split_plus);
			return (1);
		}
		else if (split_plus)
		{
			_side_rd_finder_(dst, split, split_plus);
			return ((*dst)->j + 2);
		}
		(*dst)->flex++;
		return (1);
	}
	return (0);
}

int	get_s_rd(t_bash **dst, char *op, char *split, char *split_plus)
{
	(*dst)->i = 0;
	(*dst)->j = 0;
	(*dst)->d_q = 0;
	(*dst)->s_q = 0;
	if (split_plus && split_plus[ft_strlen(split_plus) - 1] == '|')
	{
		(*dst)->op = '|';
		split_plus[ft_strlen(split_plus) - 1] = 0;
	}
	while (split && split[(*dst)->i] && op)
	{
		if (split[(*dst)->i] == '"' && !((*dst)->s_q % 2))
			(*dst)->d_q++;
		else if (split[(*dst)->i] == 39 && !((*dst)->d_q % 2))
			(*dst)->s_q++;
		if (if_operator(split + ft_strlen(split) - 1))
			(*dst)->j++;
		if (rd_dup_routine(dst, split, split_plus, op))
			break ;
		(*dst)->i++;
	}
	return (0);
}
