/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:15:22 by gothmane          #+#    #+#             */
/*   Updated: 2022/10/21 10:41:12 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	c;
	size_t	tmp;

	i = 0;
	j = 0;
	c = 0;
	tmp = 0;
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
