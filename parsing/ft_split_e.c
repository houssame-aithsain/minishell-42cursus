/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_e.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:25:33 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_countersplit_e(char *s)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] != ' ' && s[i] != '\t')
			&& (i == 0 || s[i - 1] == ' ' || s[i
					- 1] == '\t'))
			counter++;
		i++;
	}
	return (counter);
}

int	get_index_e(char *t)
{
	int	i;

	i = 0;
	while (t[i] && (t[i] != ' ' && t[i] != '\t'))
		i++;
	return (i);
}

char	**ft_split_e(char const *s)
{
	char	**strings;
	int		count;
	int		j;

	j = 0;
	if (!s)
		return (0);
	count = ft_countersplit_e((char *)s);
	strings = (char **)malloc(sizeof(char *) * (count + 1));
	if (!strings)
		return (0);
	while (*s)
	{
		if (*s == ' ' || *s == '\t')
			s++;
		else
		{
			strings[j] = ft_substr(s, 0, get_index_e((char *)s));
			j++;
			s += get_index_e((char *)s);
		}
	}
	strings[j] = 0;
	return (strings);
}
