/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:11:25 by gothmane          #+#    #+#             */
/*   Updated: 2023/04/13 23:12:29 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*cs1;
	unsigned char	*cs2;

	cs1 = (void *)s1;
	cs2 = (void *)s2;
	i = 0;
	while ((cs1[i] || cs2[i]))
	{
		if (cs1[i] == cs2[i])
			i++;
		else
			return (cs1[i] - cs2[i]);
	}
	return (0);
}
