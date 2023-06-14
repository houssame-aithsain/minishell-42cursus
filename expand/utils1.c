/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:57:19 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/14 09:12:12 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	rd_check(char *str, int i)
{
	while (i)
	{
		if (str[i] == '>' || str[i] == '<')
			return (1);
		if (str[i] == ' ')
		{
			while (str && str[i] == ' ')
				i--;
			if (str[i] == '>' || str[i] == '<')
				return (1);
			else
				return (0);
		}
		i--;
	}
	return (0);
}

int	__check_routine_(char *holder, char *tmp, int i)
{
	while (tmp && tmp[i])
	{
		if (!ft_strncmp(tmp + i, "export", 6))
		{
			while (holder[i])
			{
				if (holder[i] == '=' && holder[i + 1] == 39)
					return (-102);
				if (holder[i] == '$')
					return (0);
				i++;
			}
			return (-100);
		}
		i++;
	}
	return (0);
}

int	if_expnd(char *holder, t_ex **expn)
{
	char	*tmp;
	int		cp;
	int		i;

	i = 0;
	cp = 0;
	tmp = malloc(sizeof(char) * ft_strlen(holder) + 1);
	while (holder && holder[i])
	{
		if (holder[i] != '"' && holder[i] != 39)
			tmp[cp++] = holder[i];
		i++;
	}
	tmp[cp] = 0;
	if (__check_routine_(holder, tmp, 0))
	{
		free(tmp);
		return (-97);
	}
	free(tmp);
	return (0);
}

char	*ft_rewrite(char *holder)
{
	int	i;

	i = 0;
	while (holder && holder[i])
	{
		if (holder[i] == 10)
			holder[i] = '$';
		i++;
	}
	return (holder);
}

char	q_t(char c)
{
	char	quote_type;

	quote_type = 0;
	if (c == 39)
		quote_type = 39;
	else if (c == '"')
		quote_type = '"';
	return (quote_type);
}
