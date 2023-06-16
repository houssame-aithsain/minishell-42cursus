/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:33:05 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_exist(const char *s1, char c)
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

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		lcounter;
	int		rcounter;
	int		i;

	i = 0;
	if (!s1 || !set)
		return (0);
	lcounter = 1;
	rcounter = ft_strlen(s1) - 1;
	trimmed = (char *) malloc(sizeof(char) * (rcounter - lcounter + 1));
	if (!trimmed)
		return (NULL);
	while (lcounter < rcounter)
	{
		trimmed[i] = s1[lcounter++];
		i++;
	}
	trimmed[i] = '\0';
	return (trimmed);
}
