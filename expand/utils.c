/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 19:12:04 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/14 09:11:57 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_keys_lent(char *str)
{
	int	i;
	int	mlc;

	mlc = 0;
	i = 0;
	if (!str || !str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] != '$'))
			mlc++;
		i++;
	}
	return (mlc);
}

int	if_expn(char *str, t_ex *expn, t_list_export *exp_list)
{
	if (check_if_var(str + expn->arg_i, expn->q_type)
		&& !expn->is_heredoc && str[expn->arg_i] == '$')
		return (1);
	return (0);
}

int	is_n_heredoc(char *str, int i)
{
	if (str[i] == '|' || (str[i] == '<' && str[i + 1] != '<'
			&& str[i - 1] != '<') || (str[i] == '>' && str[i + 1] != '>'
			&& str[i - 1] != '>'))
		return (1);
	return (0);
}

int	if_valide(char *str, int i)
{
	if (str && str[i] && str[i] != ' ' && str[i] != '|' && str[i] != '"'
		&& str[i] != '-' && str[i] != 39 && str[i] != '$' && str[i] != '*'
		&& str[i] != '@' && str[i] != '+' && str[i] != '!' && str[i] != '='
		&& str[i] != '$' && (!ft_isdigit(str[i]) || !ft_isalpha(str[i])
			|| str[i] == '_'))
		return (1);
	return (0);
}

t_ex	*_q_r_change(t_ex *expn)
{
	while (expn->value && expn->value[expn->vl_i])
	{
		if (expn->value[expn->vl_i] == ' '
			&& rd_check(expn->holder, expn->arg_i))
			ft_check_ambg(expn);
		else if (expn->value[expn->vl_i] == 39)
			expn->rt_value[expn->va_l++] = 8;
		else if (expn->value[expn->vl_i] == '"')
			expn->rt_value[expn->va_l++] = 17;
		else if (expn->value[expn->vl_i] == '<')
			expn->rt_value[expn->va_l++] = 6;
		else if (expn->value[expn->vl_i] == '>')
			expn->rt_value[expn->va_l++] = 7;
		else if (expn->value[expn->vl_i] == '|')
			expn->rt_value[expn->va_l++] = 5;
		else if (expn->value[expn->vl_i] == '$')
			expn->rt_value[expn->va_l++] = 4;
		else
			expn->rt_value[expn->va_l++] = expn->value[expn->vl_i];
		expn->vl_i++;
	}
	return (expn);
}
