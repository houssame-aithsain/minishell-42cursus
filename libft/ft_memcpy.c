/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:26:53 by gothmane          #+#    #+#             */
/*   Updated: 2022/10/21 18:51:28 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*casteddst;
	char	*castedsrc;	

	i = 0;
	if (!dst && !src)
		return (0);
	castedsrc = (void *) src;
	casteddst = dst;
	while (i < n)
	{
		casteddst[i] = castedsrc[i];
		i++;
	}
	return (casteddst);
}
