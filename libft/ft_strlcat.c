/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:15:24 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
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
