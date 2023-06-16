/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_expand_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:56:47 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/14 23:16:30 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_value(char *arg, t_ex *expn, t_list_export *exp_list)
{
	int	k_len;
	int	i;

	i = 0;
	(void)exp_list;
	while (arg && arg[i] && arg[i] != expn->q_type)
	{
		k_len = -1;
		while (++k_len < expn->len)
		{
			if (expn->key && expn->key[k_len])
			{
				if (!ft_strncmp(arg + i, expn->key[k_len],
						ft_strlen(expn->key[k_len])))
					return (expn->key[k_len]);
			}
		}
		i++;
	}
	return (NULL);
}

int	check_if_var(char *str, char quote_type)
{
	int	i;

	i = 0;
	if (quote_type == 39)
		return (0);
	if (str[i] == quote_type && quote_type)
		i++;
	if (str[i] && (str[i] != quote_type || !quote_type))
	{
		while (str && str[i] && str[i] != quote_type)
		{
			if (str[i] == '$')
			{
				if (str[i + 1] == '$')
					return (0);
				if ((ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
					return (1);
				else
					return (0);
			}
			i++;
		}
	}
	return (0);
}

char	*if_status(char *holder, t_list_export *exp_list)
{
	t_format	var;

	var.in = 0;
	var.len = 0;
	var.value = NULL;
	var.arr = malloc(sizeof(char) * ft_strlen(holder) + 1);
	while (holder && holder[var.in])
	{
		if (holder[var.in] == '$' && holder[var.in + 1] == '?')
		{
			var.vl_c = 0;
			var.value = ft_strtrim(get_val_for_a_specific_key(exp_list, "\?"),
					"\1");
			while (var.value && var.value[var.vl_c])
				var.arr[var.len++] = var.value[var.vl_c++];
			var.in += 2;
			free(var.value);
		}
		else
			var.arr[var.len++] = holder[var.in++];
	}
	var.arr[var.len] = 0;
	free(holder);
	return (var.arr);
}

char	*ft_expand_vars(char *arg, t_ex *expn, t_list_export *exp_list)
{
	expn->d_q = 0;
	expn->vl_i = 0;
	expn->va_l = 0;
	expn->arg_i = 0;
	expn->q_type = 0;
	expn->is_heredoc = 0;
	expn->rt_value = malloc(sizeof(char) * ft_strlen(arg)
			+ get_value_lent(expn->key, exp_list, expn) + 1);
	while (arg && arg[expn->arg_i])
	{
		if (!ft_strncmp("<<", arg + expn->arg_i, 2))
			expn->is_heredoc = 1;
		else if (is_n_heredoc(arg, expn->arg_i))
			expn->is_heredoc = 0;
		expn->q_type = q_t(arg[expn->arg_i]);
		expn = get_add_expanded_value(arg, expn, exp_list);
	}
	expn->rt_value[expn->va_l] = 0;
	free(expn->holder);
	return (expn->rt_value);
}

t_ex	*get_expand_vars(t_list_export *exp_list, char *holder)
{
	t_ex	*expn;

	(void)exp_list;
	expn = malloc(sizeof(t_ex));
	expn->i = 0;
	expn->len = 0;
	expn->mlc = 0;
	expn->lent = 0;
	expn->error = 0;
	expn->cmd_len = 0;
	expn->key = NULL;
	expn->holder = malloc(sizeof(char) * (ft_strlen(holder) + 1));
	ft_strlcpy(expn->holder, holder, ft_strlen(holder) + 1);
	if (if_expnd(expn->holder, &expn))
		return (expn);
	expn = key_dup_routine(expn);
	expn->switcher = 1;
	expn->i = 0;
	expn->holder = ft_expand_vars(expn->holder, expn, exp_list);
	expn->holder = if_status(expn->holder, exp_list);
	expn->holder = ft_rewrite(expn->holder);
	return (expn);
}
