/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 00:58:57 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/14 09:27:22 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	arg_lent(char **arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
		i++;
	return (i);
}

int	if_q_type(char *str, int i)
{
	if (str[i] == '"')
	{
		i++;
		while (str[i] && str[i] != '"')
		{
			if (str[i] == ' ')
				str[i] = 11;
			if (str[i] == '\t')
				str[i] = 13;
			i++;
		}
	}
	else if (str[i] == 39)
	{
		i++;
		while (str[i] && str[i] != 39)
		{
			if (str[i] == ' ')
				str[i] = 11;
			if (str[i] == '\t')
				str[i] = 13;
			i++;
		}
	}
	return (i);
}

char	*spaces_trim(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		i = if_q_type(str, i);
		if (!str[i])
			break ;
		i++;
	}
	return (str);
}

void	extract_q_segments(t_format *var, t_ex *expn)
{
	while (expn->holder[var->i])
	{
		if (expn->holder[var->i] == '"')
		{
			var->container[var->j++] = expn->holder[var->i++];
			while (expn->holder[var->i] && expn->holder[var->i] != '"')
				var->container[var->j++] = expn->holder[var->i++];
			var->container[var->j++] = expn->holder[var->i++];
		}
		else if (expn->holder[var->i] == 39)
		{
			var->container[var->j++] = expn->holder[var->i++];
			while (expn->holder[var->i] && expn->holder[var->i] != 39)
				var->container[var->j++] = expn->holder[var->i++];
			var->container[var->j++] = expn->holder[var->i++];
		}
		if (expn->holder[var->i])
		{
			if (expn->holder[var->i] == '|')
				break ;
			else
				var->container[var->j++] = expn->holder[var->i++];
		}
	}
}
