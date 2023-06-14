/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_add_ex_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 09:18:31 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/14 10:16:39 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ex	*q_cp(char *arg, t_ex *expn)
{
	if (arg[expn->arg_i] == '"')
		expn->d_q++;
	if (expn->q_type == 39 && !(expn->d_q % 2))
	{
		expn->rt_value[expn->va_l++] = arg[expn->arg_i++];
		while (arg[expn->arg_i] && arg[expn->arg_i] != 39)
			expn->rt_value[expn->va_l++] = arg[expn->arg_i++];
		if (arg[expn->arg_i] == 39)
			expn->rt_value[expn->va_l++] = arg[expn->arg_i++];
	}
	else
		expn->rt_value[expn->va_l++] = arg[expn->arg_i++];
	return (expn);
}

t_ex	*amb_checker(char *arg, t_ex *expn)
{
	if (arg[expn->arg_i] == '$')
	{
		if (!expn->value && arg[expn->arg_i + 1] && arg[expn->arg_i + 1]
			!= ' ' && arg[expn->arg_i + 1] != '?'
			&& rd_check(arg, expn->arg_i - 1))
		{
			if (if_ambiguous(arg, expn->arg_i + 1))
			{
				expn->error = AR;
				expn->rt_value[expn->va_l++] = 4;
				expn->arg_i++;
			}
		}
		if (rd_check(arg, expn->arg_i - 1) && !expn->value)
			expn->error = AR;
	}
	if (arg[expn->arg_i] == '$')
		expn->arg_i++;
	if (expn->value)
	{
		expn = _q_r_change(expn);
		free(expn->value);
	}
	return (expn);
}

t_ex	*get_add_expanded_value(char *arg, t_ex *expn, t_list_export *exp_list)
{
	if (if_expn(arg, expn, exp_list))
	{
		expn->value = NULL;
		expn->vl_i = 0;
		expn->s_key = ft_get_value(arg + expn->arg_i + 1, expn, exp_list);
		if (checker_export(expn->s_key))
			expn->value = ft_strtrim(get_val_for_a_specific_key(exp_list,
						expn->s_key), "\1");
		if (arg[expn->arg_i] == expn->q_type)
			expn->rt_value[expn->va_l++] = arg[expn->arg_i++];
		expn = amb_checker(arg, expn);
		while (if_valide(arg, expn->arg_i))
			expn->arg_i++;
		if (arg[expn->arg_i] != '$' && arg[expn->arg_i]
			!= 39 && arg[expn->arg_i] != '"')
			expn->rt_value[expn->va_l++] = arg[expn->arg_i++];
		expn->rt_value[expn->va_l] = 0;
	}
	else
		q_cp(arg, expn);
	expn->rt_value[expn->va_l] = 0;
	return (expn);
}
