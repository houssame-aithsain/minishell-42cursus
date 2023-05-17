/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:25:33 by gothmane          #+#    #+#             */
/*   Updated: 2022/10/21 10:52:03 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countersplit(char *s, char c)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			counter++;
		i++;
	}
	return (counter);
}

int	get_index(char *t, char c)
{
	int	i;

	i = 0;
	while (t[i] && (t[i] != c))
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**strings;
	int		count;
	int		j;

	j = 0;
	if (!s)
		return (0);
	count = ft_countersplit((char *)s, c);
	strings = (char **) malloc(sizeof(char *) * (count + 1));
	if (!strings)
		return (0);
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			strings[j++] = ft_substr(s, 0, get_index((char *)s, c));
			s += get_index((char *)s, c);
		}
	}
	strings[j] = 0;
	return (strings);
}
