/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 03:47:15 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/11 18:12:37 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	rm_args_empty_vars(t_bash *tmp, t_bash **ptr, t_rquotes *var, t_ex *ex)
{
	if (ex->key[var->k_c])
	{
		if (!ft_strncmp(tmp->arg[var->count] + var->arg_c,
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

int	if_valide_a(t_bash *tmp, t_rquotes *var, t_ex *ex)
{
	if (tmp->arg[var->count][var->arg_c]
		&& tmp->arg[var->count][var->arg_c] == '$'
		&& tmp->arg[var->count][var->arg_c + 1]
		&& tmp->arg[var->count][var->arg_c + 1]
		!= ' ' && ex->switcher && tmp->arg[var->count][var->arg_c + 1] != '?')
		return (1);
	return (0);
}

int	if_valide_f(t_bash *tmp, t_rquotes *var, t_ex *ex)
{
	if (tmp->file[var->count][var->arg_c]
		&& tmp->file[var->count][var->arg_c] == '$'
		&& tmp->file[var->count][var->arg_c + 1]
		&& tmp->file[var->count][var->arg_c + 1]
		!= ' ' && ex->switcher && tmp->file[var->count][var->arg_c + 1] != '?')
		return (1);
	return (0);
}

void	_f_vars_reset_(t_rquotes *var)
{
	var->count = 0;
	var->arg_c = 0;
	var->s_qoute = 0;
	var->d_qoute = 0;
	var->k_c = 0;
}

void	qoutes_counter(char *arg, int *s_qoute, int *d_qoute)
{
	int	i;

	i = 0;
	*s_qoute = 0;
	*d_qoute = 0;
	while (arg && arg[i])
	{
		if (arg[i] == 39)
			*s_qoute += 1;
		if (arg[i] == '"')
			*d_qoute += 1;
		i++;
	}
}
