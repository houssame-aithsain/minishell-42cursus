/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_utils1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:30:36 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_heredocs_counter(char **redir)
{
	int	i;
	int	counter;
	int	size_redir;

	i = 0;
	counter = 0;
	if (!redir)
		return (-404);
	size_redir = 0;
	while (redir[i])
	{
		if (ft_strcmp(redir[i], "<<") == 0)
			counter++;
		i++;
	}
	return (counter);
}

char	*ft_heredoc(t_bash *cmd, t_list_export *exp)
{
	t_heredoc_data	hd;

	ft_heredoc_init(&hd);
	while (cmd && !cmd->redirection[0])
		cmd = cmd->link;
	hd.j = ft_heredocs_counter(cmd->redirection);
	while (cmd->redirection[hd.i] && hd.j != -404)
	{
		if (ft_strcmp(cmd->redirection[hd.i], "<<") == 0)
		{
			if (ft_first_heredocs(&hd, cmd, exp) == 0)
				return (0);
		}
		hd.i++;
	}
	free(hd.data_hd);
	return (0);
}
