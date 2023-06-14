/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 07:50:14 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/11 13:42:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_valide_rd(t_op *op, char *ncoom)
{
	if ((ncoom[op->i] == '>' || ncoom[op->i] == '<') && !(op->q_numb % 2)
		&& op->q_numb)
		return (1);
	return (0);
}

int	_is_rd_(t_op *op, char *ncoom)
{
	if (if_valide_rd(op, ncoom))
	{
		while (ncoom[op->i])
		{
			if (ncoom[op->i] == op->q_type)
				op->q_numb++;
			if (ncoom[op->i] == '>' || ncoom[op->i] == '<')
			{
				if (!(op->q_numb % 2) && op->q_numb)
					op->skipe = 1;
			}
			op->i++;
		}
		if (!op->skipe)
			return (0);
		else
			return (1);
	}
	return (-1);
}

int	_if_rd(t_op *op, char *ncoom)
{
	if (ncoom[op->i] == op->q_type)
	{
		while (ncoom[++op->i])
		{
			while (ncoom[op->i] && ncoom[op->i] == op->q_type)
			{
				++op->q_numb;
				op->i++;
			}
			if (!ncoom[op->i])
				break ;
			while (ncoom[op->i] && ncoom[op->i] == ' ')
				op->i++;
			if (!_is_rd_(op, ncoom))
				return (-1);
			else if (_is_rd_(op, ncoom) == 1)
				break ;
			else if (if_valide_rd(op, ncoom))
				op->skipe = 8;
		}
		if (op->skipe == 8)
			return (1);
	}
	return (0);
}

int	__rd_check_routine(t_op *op, char *ncoom)
{
	while (ncoom && ncoom[op->i] && op->q_type)
	{
		if (_if_rd(op, ncoom))
			break ;
		else if (_if_rd(op, ncoom) == -1)
			return (-1);
		if (!ncoom[op->i])
			break ;
		op->i++;
	}
	return (0);
}

char	*if_operator(char *ncoom)
{
	t_op	op;

	op.q_numb = 0;
	op.i = 0;
	op.skipe = 0;
	op.q_type = quote_t(ncoom, '"', 39, 0);
	if (__rd_check_routine(&op, ncoom) == -1)
		return (0);
	op.i = 0;
	while (ncoom && ncoom[op.i])
	{
		if (!ft_memcmp(ncoom + op.i, ">>", 2))
			return (">>\0");
		else if (!ft_memcmp(ncoom + op.i, "<<", 2))
			return ("<<\0");
		else if (ncoom[op.i] == '>')
			return (">\0");
		else if (ncoom[op.i] == '<')
			return ("<\0");
		op.i++;
	}
	return (0);
}
