/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 20:06:32 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/04/15 21:33:08 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_grep(char *line, int i, int flag)
{
	if (!flag)
	{
		if (line[i] && (line[i] == '"' || line[i] == 39)
			&& (ft_memcmp(line + i, "echo", 4
			|| ft_memcmp(line + i, "ECHO", 4))))
			return 1;
		return 0;
	}
	else if (flag == 1)
	{
		if (!ft_memcmp(line + i, "grep", 4)
			|| !ft_memcmp(line + i, "GREP", 4))
			return 1;
		return 0;
	}
	else if (flag == 2)
	{
		if (!ft_memcmp(line + i, "echo", 4)
			|| !ft_memcmp(line + i, "ECHO", 4))
			return 1;
		return 0;
	}
	return 0;
}

int	ft_loop(char *line, t_var *var)
{
	if (line[var->quote_count] && var->if_quote
		&& (line[var->quote_count] != '"'
		|| line[var->quote_count] != 39))
		return 1;
	return 0;
}