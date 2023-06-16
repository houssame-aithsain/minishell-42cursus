/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unquote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 05:38:26 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/14 23:08:31 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	if_empty_cmd(t_bash *tmp, t_bash **ptr, t_rquotes *var, t_ex *ex)
{
	(void)ptr;
	while (var->k_c < ex->len)
	{
		if (tmp->command[var->arg_c] == '$' && (!tmp->command[var->arg_c + 1]
				|| tmp->command[var->arg_c + 1] == ' '))
		{
			var->command[var->arg_c++] = tmp->command[var->cmd_c++];
			return (1);
		}
		if (ft_isdigit(tmp->command[var->cmd_c])
			|| tmp->command[var->cmd_c] == '@')
		{
			var->cmd_c++;
			return (1);
		}
		if (rm_cmd_empty_vars(tmp, ptr, var, ex))
			return (1);
		var->k_c++;
	}
	return (0);
}

int	__if_cmd(t_bash *tmp, t_bash **ptr, t_rquotes *var, t_ex *ex)
{
	if (tmp->command[var->cmd_c] == 39)
	{
		var->qoute_type = 39;
		str_cp(tmp->command, var, 0, ptr);
	}
	else if (tmp->command[var->cmd_c] == '"')
	{
		var->qoute_type = '"';
		str_cp(tmp->command, var, 0, ptr);
	}
	else if (if_valide_c(tmp, var, ex))
	{
		var->k_c = 0;
		var->cmd_c++;
		if (if_empty_cmd(tmp, ptr, var, ex))
			return (1);
	}
	else
		var->command[var->arg_c++] = tmp->command[var->cmd_c++];
	return (0);
}

void	_cmd_q_rm(t_bash *tmp, t_bash **ptr, t_rquotes *var, t_ex *ex)
{
	var->count = 0;
	var->arg_c = 0;
	var->cmd_c = 0;
	var->command = malloc(sizeof(char) * ft_strlen(tmp->command) + 1);
	var->arg = malloc(sizeof(char *) * (arg_lent(tmp->arg) + 1));
	while (tmp->command[var->cmd_c])
	{
		if (__if_cmd(tmp, ptr, var, ex))
			break ;
	}
	var->command[var->arg_c] = 0;
	if (!var->command[0] && var->cmd_c == 2)
	{
		var->command[0] = 6;
		var->command[1] = 0;
	}
}

void	quote_sanitizer(t_bash **ptr, t_ex *ex)
{
	t_bash		*tmp;
	t_rquotes	var;

	_q_vars_reset_(&var);
	if (!ptr || !*ptr)
		return ;
	tmp = *ptr;
	_s_q_c(ptr, tmp, &var);
	while (tmp)
	{
		_cmd_q_rm(tmp, ptr, &var, ex);
		_args_q_rm(tmp, ptr, &var, ex);
		_files_q_rm(tmp, ptr, &var, ex);
		ft_free_q(tmp);
		tmp->file = var.file;
		tmp->command = var.command;
		tmp->arg = var.arg;
		tmp = tmp->link;
	}
}
