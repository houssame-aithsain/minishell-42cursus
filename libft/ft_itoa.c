/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:37:40 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_counter(long n)
{	
	int		i;

	i = 1;
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n / 10 > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	ft_fillin(char *ms, int counter, long n)
{
	int	s;

	s = 0;
	if (n < 0)
	{
		n *= -1;
		ms[0] = '-';
		s = 1;
	}
	counter--;
	while (counter >= s)
	{
		ms[counter] = (n % 10) + 48;
		n = n / 10;
		counter--;
	}
}

char	*ft_itoa(int n)
{
	int		i;
	char	*ms;
	int		sign;
	long	ln;

	sign = 0;
	ln = n;
	i = ft_counter(ln);
	ms = malloc(i + 1);
	if (!ms)
		return (0);
	ms[i] = '\0';
	ft_fillin(ms, i, ln);
	return (ms);
}
