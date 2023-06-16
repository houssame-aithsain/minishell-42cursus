/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 02:07:06 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/14 23:13:23 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_pipe(char *str, int flag)
{
	int	i;

	i = 0;
	if (flag)
	{
		while (str && str[i])
		{
			if (str[i] == '|' && !str[i + 1])
				return (1);
			i++;
		}
		return (0);
	}
	while (str && str[i])
	{
		if (str[i++] != '|')
			return (1);
	}
	return (0);
}

char	_get_q_type(char *str, int i)
{
	int	quote_type;

	quote_type = 0;
	while (str && str[i])
	{
		if (str[i] == '"')
		{
			quote_type = '"';
			break ;
		}
		if (str[i] == 39)
		{
			quote_type = 39;
			break ;
		}
		i++;
	}
	return (quote_type);
}

int	get_operator_length(char *str)
{
	int	i;
	int	quote_count;
	int	quote_type;

	quote_count = 0;
	quote_type = _get_q_type(str, 0);
	i = 0;
	while (str && str[i])
	{
		if ((str[i] == '>' || str[i] == '<') && !(quote_count % 2))
			break ;
		if (str[i] == quote_type)
			quote_count++;
		i++;
	}
	return (i);
}

void	n_remove(char *file)
{
	int	space;

	space = 0;
	while (file && file[space])
	{
		if (file[space] == 11)
			file[space] = ' ';
		if (file[space] == 13)
			file[space] = '\t';
		space++;
	}
}
