/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_cp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:41:38 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/11 18:42:52 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_rquotes	*_var_changer(t_rquotes *var, int flag)
{
	if (!flag)
	{
		var->c_c = &var->cmd_c;
		var->a_c = &var->arg_c;
		var->cmd = var->command;
	}
	else if (flag == 2)
	{
		var->c_c = &var->arg_c;
		var->a_c = &var->arg_count;
		var->cmd = var->file[var->count];
	}
	else
	{
		var->c_c = &var->arg_c;
		var->a_c = &var->arg_count;
		var->cmd = var->arg[var->count];
	}
	return (var);
}

void	str_cp(char *dst, t_rquotes *var, int flag, t_bash **ptr)
{
	var = _var_changer(var, flag);
	var->quote_numb = 1;
	(*var->c_c)++;
	while (dst[*var->c_c])
	{
		if (dst[*var->c_c] == '"' || dst[*var->c_c] == 39)
		{
			if (dst[*var->c_c] == var->qoute_type)
				var->quote_numb++;
			if (dst[*var->c_c] != var->qoute_type && !(var->quote_numb % 2))
				break ;
		}
		if (dst[*var->c_c] != var->qoute_type)
			var->cmd[(*var->a_c)++] = dst[*var->c_c];
		(*var->c_c)++;
	}
	var->cmd[*var->a_c] = 0;
}
