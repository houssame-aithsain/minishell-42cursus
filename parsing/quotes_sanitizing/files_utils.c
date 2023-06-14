/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:15:11 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/14 09:29:43 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	__q_r_arg(t_bash **ptr, int i, int j)
{
	while ((*ptr)->arg[i])
	{
		j = 0;
		while ((*ptr)->arg[i][j])
		{
			if (((*ptr)->arg)[i][j] == 8)
				((*ptr)->arg)[i][j] = 39;
			else if (((*ptr)->arg)[i][j] == 17)
				((*ptr)->arg)[i][j] = '"';
			else if (((*ptr)->arg)[i][j] == 6)
				((*ptr)->arg)[i][j] = '<';
			else if (((*ptr)->arg)[i][j] == 7)
				((*ptr)->arg)[i][j] = '>';
			else if (((*ptr)->arg)[i][j] == 5)
				((*ptr)->arg)[i][j] = '|';
			else if (((*ptr)->arg)[i][j] == 4)
				((*ptr)->arg)[i][j] = '$';
			else if (((*ptr)->arg)[i][j] == 13)
				((*ptr)->arg)[i][j] = '\t';
			j++;
		}
		i++;
	}
}

void	__q_r_file(t_bash **ptr, int i, int j)
{
	while ((*ptr)->file[i])
	{
		j = 0;
		while ((*ptr)->file[i][j])
		{
			if ((*ptr)->file[i][j] == 4)
				(*ptr)->error = AR;
			if (((*ptr)->file)[i][j] == 8)
				((*ptr)->file)[i][j] = 39;
			else if (((*ptr)->file)[i][j] == 17)
				((*ptr)->file)[i][j] = '"';
			else if (((*ptr)->file)[i][j] == 1)
				((*ptr)->file)[i][j] = 39;
			else if (((*ptr)->file)[i][j] == 2)
				((*ptr)->file)[i][j] = '"';
			else if (((*ptr)->file)[i][j] == 11)
				((*ptr)->file)[i][j] = ' ';
			else if (((*ptr)->file)[i][j] == 13)
				((*ptr)->file)[i][j] = '\t';
			j++;
		}
		i++;
	}
}

void	__q_r_cmd(t_bash **ptr, int i)
{
	while ((*ptr)->command && ((*ptr)->command)[i])
	{
		if (((*ptr)->command)[i] == 8)
			((*ptr)->command)[i] = 39;
		else if (((*ptr)->command)[i] == 17)
			((*ptr)->command)[i] = '"';
		else if (((*ptr)->command)[i] == 6)
			((*ptr)->command)[i] = '<';
		else if (((*ptr)->command)[i] == 7)
			((*ptr)->command)[i] = '>';
		else if (((*ptr)->command)[i] == 5)
			((*ptr)->command)[i] = '|';
		else if (((*ptr)->command)[i] == 4)
			((*ptr)->command)[i] = '$';
		else if (((*ptr)->command)[i] == 13)
			((*ptr)->command)[i] = '\t';
		i++;
	}
}

void	quotes_rewriter(t_bash **ptr)
{
	t_bash	*tmp;
	t_bash	*head;

	tmp = *ptr;
	head = tmp;
	while (tmp)
	{
		__q_r_cmd(ptr, 0);
		__q_r_arg(ptr, 0, 0);
		__q_r_file(ptr, 0, 0);
		tmp = tmp->link;
	}
	ptr = &head;
}
