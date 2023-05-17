/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:58:56 by gothmane          #+#    #+#             */
/*   Updated: 2022/10/21 10:09:41 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*n;

	count = 0;
	n = NULL;
	if (!lst)
		return (0);
	n = lst;
	while (n)
	{
		count++;
		n = n->next;
	}
	return (count);
}
