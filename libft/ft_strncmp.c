/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:11:25 by gothmane          #+#    #+#             */
/*   Updated: 2023/05/09 17:29:43 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int				i;
	unsigned char	*cs1;
	unsigned char	*cs2;

	cs1 = (void *)s1;
	cs2 = (void *)s2;
	i = 0;
	while ((cs1[i] || cs2[i]) && i < n)
	{
		if (cs1[i] == cs2[i])
			i++;
		else
			return (cs1[i] - cs2[i]);
	}
	return (0);
}
