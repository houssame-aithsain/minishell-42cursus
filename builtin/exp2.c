/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:34:31 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list_export	*ft_lstnew_mod(char *content)
{
	t_list_export	*ls;
	int				i;
	char			*key;
	char			*value;
	char			*declare;

	i = 0;
	ls = malloc(sizeof(t_list_export));
	declare = "declare -x ";
	key = ft_getkey(content);
	value = ft_getvalue(content);
	if (!ls)
		return (0);
	ls->key = key;
	ls->value = value;
	declare = ft_strjoin_bb(declare, ls->key);
	if (ft_detect_equal(ls->key, content) == 0)
		declare = ft_strjoin(declare, "=");
	if (ls->value)
		declare = ft_strjoin(declare, ls->value);
	ls->content = declare;
	ls->next = NULL;
	return (ls);
}

int	ft_exist_(const char *s1, char c)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	getlindex(const char *s1, const char *set)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (!ft_exist_(set, s1[i]))
			return (i);
		i++;
	}
	return (-1);
}

int	getrindex(const char *s1, const char *set)
{
	int	lengths1;

	lengths1 = ft_strlen(s1);
	while (lengths1 > 0)
	{
		if (!ft_exist_(set, s1[lengths1 - 1]))
			return (lengths1);
		lengths1--;
	}
	return (-1);
}

char	*ft_strtrim_exp_free(char *s1, char const *set)
{
	char	*trimmed;
	int		lcounter;
	int		rcounter;
	int		i;

	i = 0;
	if (!s1 || !set)
		return (0);
	lcounter = getlindex(s1, set);
	rcounter = getrindex(s1, set);
	trimmed = (char *)malloc(sizeof(char) * (rcounter - lcounter + 1));
	if (!trimmed)
		return (NULL);
	while (lcounter < rcounter)
	{
		trimmed[i] = s1[lcounter++];
		i++;
	}
	trimmed[i] = '\0';
	free(s1);
	return (trimmed);
}
