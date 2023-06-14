/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:13:24 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/14 10:32:15 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_ambiguous(char *arg, int i)
{
	while (arg && arg[i] && (ft_isalpha(arg[i]) || ft_isdigit(arg[i])
			|| arg[i] == '_'))
		i++;
	if (arg[i] && (arg[i] == '+' || arg[i] == '-' || arg[i] == '!'
			|| arg[i] == '=' || arg[i] == '$'))
		return (0);
	if (!arg[i])
		return (1);
	return (0);
}

void	ft_check_ambg(t_ex *expn)
{
	int	i;

	i = 0;
	while (expn->value && expn->value[i] && expn->value[i] == ' ')
		i++;
	while (expn->value && expn->value[i])
	{
		if (expn->value[i] == ' ' && expn->value[i + 1]
			&& expn->value[i + 1] != ' ')
			expn->error = AR;
		i++;
	}
	expn->rt_value[expn->va_l++] = expn->value[expn->vl_i];
}

int	get_value_lent(char **key, t_list_export *exp_list, t_ex *expn)
{
	int		len;
	int		j;
	int		i;
	char	*value;

	i = 0;
	len = 0;
	value = NULL;
	while (key && i < expn->len)
	{
		j = 0;
		if (checker_export(key[i]))
		{
			value = ft_strtrim(get_val_for_a_specific_key(exp_list,
						key[i]), "\1");
			while (value && value[j])
				j++;
			len += j;
			if (value)
				free(value);
		}
		i++;
	}
	return (len);
}
