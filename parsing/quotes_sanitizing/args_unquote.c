/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_unquote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 04:12:12 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/11 18:13:27 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	if_empty_args(t_bash *tmp, t_bash **ptr, t_rquotes *var, t_ex *ex)
{
	while (var->k_c < ex->len)
	{
		if (ft_isdigit(tmp->arg[var->count][var->arg_c])
			|| tmp->arg[var->count][var->arg_c] == '@')
		{
			var->arg_c++;
			break ;
		}
		if (rm_args_empty_vars(tmp, ptr, var, ex))
			break ;
		var->k_c++;
	}
	return (0);
}

int	__if_args(t_bash *tmp, t_bash **ptr, t_rquotes *var, t_ex *ex)
{
	if (tmp->arg[var->count][var->arg_c] == 39)
	{
		var->qoute_type = 39;
		str_cp(tmp->arg[var->count], var, 1, ptr);
	}
	else if (tmp->arg[var->count][var->arg_c] == '"')
	{
		var->qoute_type = '"';
		str_cp(tmp->arg[var->count], var, 1, ptr);
	}
	else if (if_valide_a(tmp, var, ex))
	{
		var->k_c = 0;
		var->arg_c++;
		if_empty_args(tmp, ptr, var, ex);
	}
	else
		var->arg[var->count][var->arg_count++]
			= tmp->arg[var->count][var->arg_c++];
	return (0);
}

void	_args_q_rm(t_bash *tmp, t_bash **ptr, t_rquotes *var, t_ex *ex)
{
	while (tmp->arg[var->count])
	{
		var->arg_c = 0;
		var->arg_count = 0;
		var->arg[var->count]
			= malloc(sizeof(char) * ft_strlen(tmp->arg[var->count]) + 1);
		qoutes_counter(tmp->arg[var->count], &var->s_qoute, &var->d_qoute);
		while (tmp->arg[var->count] && tmp->arg[var->count][var->arg_c])
		{
			if (__if_args(tmp, ptr, var, ex))
				break ;
		}
		var->arg[var->count][var->arg_count] = 0;
		var->count++;
	}
	var->arg[var->count] = NULL;
}
