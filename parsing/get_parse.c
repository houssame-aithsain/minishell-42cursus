/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:49:57 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/14 22:02:37 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	_s_str_(char *str, t_cp *var, t_bash *dst)
{
	int	i;
	int	j;

	i = 0;
	var->split = ft_split_e(str);
	while (var->split[i])
		i++;
	dst->arg = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (var->split && var->split[i])
	{
		j = 0;
		while (var->split[i][j])
		{
			if (var->split[i][j] == '>' || var->split[i][j] == '<')
				dst->rd_count++;
			j++;
		}
		i++;
	}
	dst->rd_count++;
	dst->file = malloc(sizeof(char *) * dst->rd_count);
	dst->command = malloc(sizeof(char) * (ft_strlen(var->split[0]) + 1));
	dst->redirection = malloc(sizeof(char *) * dst->rd_count);
}

void	_cmd_dup_(t_cp *var, t_bash *dst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	var->quote_type = quote_t(var->split[i], '"', 39, 0);
	while (var->split && var->split[i] && var->split[i][j])
	{
		if (var->split[i][j] == var->quote_type)
			var->q_count++;
		if (var->split[i][j] == '|' && !(var->q_count % 2))
		{
			dst->op = var->split[i][j];
			var->split[i][j] = 0;
			break ;
		}
		dst->command[j] = var->split[i][j];
		j++;
	}
	dst->command[j] = 0;
}

void	_rd_dup_(t_cp *var, t_bash *dst)
{
	while (var->split && var->split[var->i] && if_operator(var->split[var->i]))
	{
		var->check = get_s_rd(&dst, if_operator(var->split[var->i]),
				var->split[var->i], var->split[var->i + 1]);
		if (var->check == 2 || var->check > 2)
		{
			if (var->split[var->i] && var->split[var->i][0])
			{
				dst->arg[var->j] = malloc(sizeof(char)
						* ft_strlen(var->split[var->i]) + 1);
				ft_strlcpy(dst->arg[var->j], var->split[var->i],
					ft_strlen(var->split[var->i]) + 1);
				var->j++;
			}
			if (var->check == 2)
				var->i++;
			else
				var->i += 2;
		}
		else
			break ;
		if (!var->split[var->i])
			break ;
	}
}

void	_arg_dup_(t_cp *var, t_bash *dst)
{
	var->space = 0;
	dst->arg[var->j] = malloc(sizeof(char) * ft_strlen(var->split[var->i]) + 1);
	ft_strlcpy(dst->arg[var->j], var->split[var->i],
		ft_strlen(var->split[var->i]) + 1);
	if (dst->arg[var->j] && (dst->arg[var->j][ft_strlen(dst->arg[var->j])
			- 1] == '|' || if_operator(dst->arg[var->j])))
		dst->arg[var->j][ft_strlen(dst->arg[var->j]) - 1] = 0;
	while (dst->arg[var->j] && dst->arg[var->j][var->space])
	{
		if (dst->arg[var->j][var->space] == 11)
			dst->arg[var->j][var->space] = ' ';
		var->space++;
	}
	var->j++;
}

void	get_parse(t_bash *dst, char *str)
{
	t_cp	var;

	_vars_reset(&var, dst);
	_s_str_(str, &var, dst);
	_cmd_dup_(&var, dst);
	n_remove(dst->command);
	if (var.split[0])
		if (get_s_rd(&dst, if_operator(dst->command), dst->command,
				var.split[var.i + 1]) >= 2)
			var.i++;
	while (var.split[0] && var.split[++var.i])
	{
		_pipe_checker(&var, dst);
		_rd_dup_(&var, dst);
		if (!var.split[var.i])
			break ;
		if (var.split[var.i] && if_pipe(var.split[var.i], 0))
			_arg_dup_(&var, dst);
		_pipe_checker(&var, dst);
	}
	ft_free(&var, dst);
}
