/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_unquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 06:44:40 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/14 23:06:05 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	rm_file_empty_vars(t_bash *tmp, t_bash **ptr, t_rquotes *var, t_ex *ex)
{
	(void)ptr;
	if (ex->key[var->k_c])
	{
		if (!ft_strncmp(tmp->file[var->count] + var->arg_c,
				ex->key[var->k_c], ft_strlen(ex->key[var->k_c])))
		{
			var->l_s = ft_strlen(ex->key[var->k_c]);
			var->k_c = 0;
			while (var->k_c < var->l_s)
			{
				var->k_c++;
				var->arg_c++;
			}
			return (1);
		}
	}
	return (0);
}

int	if_empty_files(t_bash *tmp, t_bash **ptr, t_rquotes *var, t_ex *ex)
{
	while (var->k_c < ex->len)
	{
		if (ft_isdigit(tmp->file[var->count][var->arg_c])
			|| tmp->file[var->count][var->arg_c] == '@')
		{
			var->arg_c++;
			if (!tmp->file[var->count][var->arg_c])
				tmp->error = AR;
			break ;
		}
		if (rm_file_empty_vars(tmp, ptr, var, ex))
			break ;
		var->k_c++;
	}
	return (0);
}

void	_if_s_d_q(t_bash *tmp, t_bash **ptr, t_rquotes *var, t_ex *ex)
{
	while (tmp->file[var->count] && tmp->file[var->count][var->arg_c])
	{
		if (tmp->file[var->count][var->arg_c] == 39)
		{
			var->qoute_type = 39;
			str_cp(tmp->file[var->count], var, 2, ptr);
		}
		else if (tmp->file[var->count][var->arg_c] == '"')
		{
			var->qoute_type = '"';
			str_cp(tmp->file[var->count], var, 2, ptr);
		}
		else if (if_valide_f(tmp, var, ex) && !ex->is_heredoc)
		{
			var->k_c = 0;
			var->arg_c++;
			if_empty_files(tmp, ptr, var, ex);
		}
		else
			var->file[var->count][var->arg_count++]
				= tmp->file[var->count][var->arg_c++];
	}
}

void	__if_file(t_bash *tmp, t_bash **ptr, t_rquotes *var, t_ex *ex)
{
	var->arg_c = 0;
	var->arg_count = 0;
	var->file[var->count]
		= malloc(sizeof(char) * ft_strlen(tmp->file[var->count]) + 1);
	qoutes_counter(tmp->file[var->count], &var->s_qoute, &var->d_qoute);
	_if_s_d_q(tmp, ptr, var, ex);
	var->file[var->count][var->arg_count] = 0;
}

void	_files_q_rm(t_bash *tmp, t_bash **ptr, t_rquotes *var, t_ex *ex)
{
	_f_vars_reset_(var);
	var->file = malloc(sizeof(char *) * (arg_lent(tmp->file) + 1));
	while (tmp->file[var->count])
	{
		__if_file(tmp, ptr, var, ex);
		var->count++;
	}
	var->file[var->count] = NULL;
}
