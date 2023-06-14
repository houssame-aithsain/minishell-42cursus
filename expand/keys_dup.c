/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 21:35:30 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/14 09:13:57 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_key_dup(char *str)
{
	int		i;
	char	*value;

	i = 0;
	value = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (if_valide(str, i))
	{
		value[i] = str[i];
		i++;
	}
	if (!i)
	{
		free(value);
		return (NULL);
	}
	value[i] = 0;
	return (value);
}

int	get_key(char *arg, char **str)
{
	int	i;

	i = 0;
	while (arg && arg[i])
	{
		if (arg[i] == '$' && arg[i + 1] != '$')
		{
			*str = ft_key_dup(arg + i + 1);
			i++;
			while (arg[i] && arg[i] != '$')
				i++;
			return (i);
		}
		i++;
	}
	str = NULL;
	return (i);
}

t_ex	*key_dup_routine(t_ex *expn)
{
	expn->mlc = get_keys_lent(expn->holder);
	expn->key = malloc(sizeof(char *) * (expn->mlc + 1));
	while (expn->len < expn->mlc)
	{
		if (expn->holder && expn->cmd_len <= ft_strlen(expn->holder))
			expn->cmd_len += get_key(expn->holder + expn->cmd_len,
					&expn->key[expn->len]);
		if (expn->key[expn->len])
			expn->cmd_len += expn->lent;
		expn->len++;
	}
	expn->key[expn->len] = NULL;
	return (expn);
}
