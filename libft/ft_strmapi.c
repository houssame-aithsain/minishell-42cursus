/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:43:56 by gothmane          #+#    #+#             */
/*   Updated: 2022/10/21 11:06:38 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*mas;

	if (!s)
		return (0);
	mas = malloc(ft_strlen(s) + 1);
	if (!mas)
		return (0);
	i = 0;
	while (s[i])
	{
		mas[i] = f(i, s[i]);
		i++;
	}
	mas[i] = '\0';
	return (mas);
}
