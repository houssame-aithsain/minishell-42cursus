/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_cmd_finder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:46:49 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/14 10:13:07 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bash	*cmd_r(t_bash *tmp, int i)
{
	if (!tmp->command[0] && tmp->arg[0] && (!(ft_strncmp(tmp->redirection[0],
					"<<", 2)) || !(ft_strncmp(tmp->redirection[0], ">>", 2))
			|| !(ft_strncmp(tmp->redirection[0], ">", 1))
			|| !(ft_strncmp(tmp->redirection[0], "<", 1))))
	{
		free(tmp->command);
		tmp->command = tmp->arg[0];
		while (tmp->arg[i])
		{
			tmp->arg[i] = tmp->arg[i + 1];
			i++;
		}
	}
	return (tmp);
}

void	heredoc_cmd_finder(t_bash **ptr)
{
	t_bash	*tmp;
	int		i;

	tmp = *ptr;
	while (tmp)
	{
		tmp = cmd_r(tmp, 0);
		i = 0;
		while (tmp->file && tmp->file[0] && tmp->file[0][i])
		{
			if (tmp->file[0][i] == 39 || tmp->file[0][i] == '"')
			{
				tmp->h_expn = 1;
				return ;
			}
			i++;
		}
		tmp->h_expn = 0;
		tmp = tmp->link;
	}
}
