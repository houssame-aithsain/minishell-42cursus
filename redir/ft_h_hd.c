/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_h_hd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:42:51 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	_ft_init_exp_helper(t_exp_helper *seh, char *arg)
{
	(*seh).e = 0;
	(*seh).k = 0;
	(*seh).ee = ft_split(arg, '$');
	if (!(*seh).ee || ft_check_dollar_sign(arg) == 0)
	{
		ft_free_args((*seh).ee);
		return (0);
	}
	return (1);
}

char	**ft_exp_here_helper(char *arg, t_list_export *exp)
{
	t_exp_helper	seh;

	if (_ft_init_exp_helper(&seh, arg) == 0)
		return (NULL);
	while (seh.ee[seh.e])
	{
		seh.k = 0;
		while (seh.ee[seh.e][seh.k] && seh.ee[seh.e][seh.k] != 39
			&& seh.ee[seh.e][seh.k] != ' ' && seh.ee[seh.e][seh.k] != '-'
			&& seh.ee[seh.e][seh.k] != '"' && seh.ee[seh.e][seh.k] != '$'
			&& seh.ee[seh.e][seh.k] != '*' && seh.ee[seh.e][seh.k] != '@' &&
				(ft_isdigit(seh.ee[seh.e][seh.k])
						|| ft_isalpha(seh.ee[seh.e][seh.k])
						|| seh.ee[seh.e][seh.k] == '_'
						|| seh.ee[seh.e][seh.k] == '?'))
			seh.k++;
		if (seh.k > 0)
			ft_sup_exp_here_helper(&seh.ee[seh.e], exp, seh.k, &seh);
		seh.e++;
	}
	return (seh.ee);
}

char	*ft_expand_in_heredoc(char *arg, t_list_export *ex)
{
	t_exp_h	exp;

	ft_exp_h_init(&exp);
	if (arg)
	{
		exp.ee = ft_exp_here_helper(arg, ex);
		if (exp.ee && exp.ee[0])
		{
			exp.joined = ft_strdup(exp.ee[0]);
			free(exp.ee[0]);
		}
		else
			return (NULL);
		exp.e = 1;
		while (exp.ee[exp.e])
		{
			exp.joined = ft_strjoin(exp.joined, exp.ee[exp.e]);
			free(exp.ee[exp.e]);
			exp.e++;
		}
		free(exp.ee);
		return (exp.joined);
	}
	return (0);
}
