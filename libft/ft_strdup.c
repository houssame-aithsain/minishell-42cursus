/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:33:38 by gothmane          #+#    #+#             */
/*   Updated: 2022/10/17 14:52:10 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		sizes1;
	char	*clone;
	int		i;

	i = 0;
	sizes1 = ft_strlen(s1);
	clone = malloc(sizes1 * sizeof(char) + 1);
	if (!clone)
		return (0);
	while (s1[i])
	{
		clone[i] = s1[i];
		i++;
	}
	clone[i] = '\0';
	return (clone);
}
