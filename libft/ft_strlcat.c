/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:15:24 by gothmane          #+#    #+#             */
/*   Updated: 2022/10/17 14:48:54 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	length_src;
	size_t	length_dst;
	size_t	cons;

	i = 0;
	if (!dstsize && dst == NULL)
		return (ft_strlen(src));
	length_dst = ft_strlen(dst);
	length_src = ft_strlen(src);
	if (dstsize <= ft_strlen(dst))
		return (ft_strlen(src) + dstsize);
	cons = dstsize - ft_strlen(dst) - 1;
	while (src[i] && i < cons)
	{
		dst[length_dst + i] = src[i];
		i++;
	}
	dst[length_dst + i] = 0;
	return (length_src + length_dst);
}
