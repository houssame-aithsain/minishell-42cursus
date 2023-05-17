/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:22:17 by gothmane          #+#    #+#             */
/*   Updated: 2023/05/13 15:51:19 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*substring;
	unsigned int		i;
	size_t				j;

	i = 0;
	j = start;
	if (!s)
		return (0);
	if (len >= ft_strlen(s))
		len = ft_strlen(s);
	if (start >= ft_strlen(s))
		return (ft_calloc(1, 1));
	substring = malloc (len + 1);
	if (!substring)
		return (0);
	while (s[j] && i < len)
	{
		substring[i++] = s[j++];
	}
	substring[i] = '\0';
	return (substring);
}
