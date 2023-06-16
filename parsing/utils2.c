/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 08:40:12 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/14 23:11:08 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	_vars_reset(t_cp *var, t_bash *dst)
{
	var->i = 0;
	var->j = 0;
	var->check = 0;
	var->space = 0;
	var->q_count = 0;
	dst->rd_count = 0;
	dst->flex = 0;
	dst->op = 0;
	dst->file_free = 0;
	dst->red_free = 0;
	dst->redirection = NULL;
	dst->file = NULL;
	dst->command = NULL;
}

void	ft_free(t_cp *var, t_bash *dst)
{
	int	i;

	i = 0;
	while (var->split[i])
		free(var->split[i++]);
	free(var->split);
	dst->redirection[dst->red_free] = NULL;
	dst->file[dst->file_free] = NULL;
	dst->arg[var->j] = NULL;
}

void	_pipe_checker(t_cp *var, t_bash *dst)
{
	if (if_pipe(var->split[var->i], 1))
	{
		dst->op = '|';
		var->split[var->i][ft_strlen(var->split[var->i]) - 1] = 0;
	}
}

char	_s_d_quote_t(char *ncoom, char f_type, char s_type)
{
	int		i;
	char	quote_type;

	quote_type = 0;
	i = 0;
	while (ncoom && ncoom[i] && ncoom[i] != '$')
	{
		if (ncoom[i] == f_type)
		{
			quote_type = f_type;
			break ;
		}
		if (ncoom[i] == s_type)
		{
			quote_type = s_type;
			break ;
		}
		i++;
	}
	return (quote_type);
}

char	quote_t(char *ncoom, char f_type, char s_type, int flag)
{
	char	quote_type;
	int		i;

	i = 0;
	quote_type = 0;
	if (flag)
	{
		quote_type = _s_d_quote_t(ncoom, f_type, s_type);
		return (quote_type);
	}
	while (ncoom && ncoom[i])
	{
		if (ncoom[i] == f_type)
		{
			quote_type = f_type;
			break ;
		}
		if (ncoom[i] == s_type)
		{
			quote_type = s_type;
			break ;
		}
		i++;
	}
	return (quote_type);
}
