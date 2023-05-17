/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:42:42 by gothmane          #+#    #+#             */
/*   Updated: 2022/10/21 10:04:59 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*cv;
	size_t	nbits;

	nbits = count * size;
	cv = malloc(nbits);
	if (count == SIZE_MAX || size == SIZE_MAX)
		return (0);
	if (cv)
	{
		ft_bzero(cv, nbits);
		return (cv);
	}
	else
		return (0);
}
