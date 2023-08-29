/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_access.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:46:13 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_access_redir(t_bash *cmd)
{
	int	i;
	int	fd;

	i = 0;
	fd = -1;
	if (!cmd)
		return (404);
	while (cmd->redirection[i])
	{
		if (ft_strncmp(cmd->redirection[i], ">", 2) == 0)
		{
			if (ft_access_red(cmd->file[i]) == -1)
				fd = open(cmd->file[i], O_CREAT, 0664);
			else
				fd = open(cmd->file[i], O_TRUNC, NULL);
			close(fd);
		}
		i++;
	}
	return (1);
}

int	ft_check_access_inred(t_bash *cmd)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	if (!cmd)
		return (404);
	while (cmd->redirection[i])
	{
		if (ft_strncmp(cmd->redirection[i], "<", 2) == 0)
		{
			counter++;
			if (ft_access_red(cmd->file[i]) == -1)
			{
				printf("ERROR FILE NOT FOUND %s\n", cmd->file[i]);
				return (-1);
			}
		}
		i++;
	}
	if (counter == 0)
		return (-2);
	return (1);
}

int	_ft_first_condition_in(t_bash *cmd, t_redir_in *ins)
{
	(void)cmd;
	if (ft_strcmp((*ins).last_c->redirection[(*ins).i], "<") == 0
		|| ft_strcmp((*ins).last_c->redirection[(*ins).i], "<<") == 0)
	{
		if ((((*ins).last_c->file[(*ins).i]
					&& (*ins).last_c->file[(*ins).i][0] == 4)
			|| (*ins).last_c->error == 10))
			return (-18);
		if ((ft_strncmp((*ins).last_c->redirection[(*ins).i], "<", 2) == 0
				&& access((*ins).last_c->file[(*ins).i], F_OK) != 0))
			return (-400);
		(*ins).last = (*ins).i;
	}
	return (1);
}
