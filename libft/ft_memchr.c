/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:02:37 by gothmane          #+#    #+#             */
/*   Updated: 2022/10/01 17:58:52 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char			*cass;
	size_t			i;

	cass = (void *) s;
	i = 0;
	if (n > 0)
	{
		while (i < n)
		{
			if ((char) c == cass[i])
				return ((char *)&cass[i]);
			i++;
		}
	}
	return (0);
}
