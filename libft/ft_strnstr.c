/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:15:22 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	c;

	i = 0;
	j = 0;
	c = 0;
	while (needle[j] && i < len && haystack[i])
	{
		if (haystack[i] == needle[j] && j < ft_strlen(needle))
			j++;
		else
		{
			j = 0;
			i = 0;
			i = i + c;
			c++;
		}
		i++;
	}
	if (j == ft_strlen(needle))
		return ((char *)&haystack[i - ft_strlen(needle)]);
	return (0);
}
