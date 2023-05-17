/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 12:54:32 by gothmane          #+#    #+#             */
/*   Updated: 2022/10/01 16:30:44 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	j;
	int	check;
	int	size;

	i = 0;
	j = 0;
	check = 0;
	size = ft_strlen(s);
	while (i <= size)
	{
		if (s[i] == (char)c)
		{
			j = i;
			check = 1;
		}	
		i++;
	}
	if (check)
		return ((char *) &s[j]);
	return (0);
}
