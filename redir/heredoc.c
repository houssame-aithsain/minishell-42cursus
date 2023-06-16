/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:55:20 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sup_last_hd(t_heredoc_data *hd, t_bash *cmd, t_list_export *exp)
{
	(*hd).temp = ft_expand_in_heredoc((*hd).arr, exp);
	if ((*hd).temp && cmd->h_expn == 0 && ft_strcmp((*hd).eof, (*hd).arr) != 0)
	{
		if (!(*hd).data_hd)
			(*hd).data_hd = ft_strjoin_bb((*hd).data_hd, (*hd).temp);
		else
			(*hd).data_hd = ft_strjoin((*hd).data_hd, (*hd).temp);
		(*hd).data_hd = ft_strjoin((*hd).data_hd, "\n");
	}
	else
	{
		(*hd).data_hd = ft_strjoin((*hd).data_hd, (*hd).arr);
		(*hd).data_hd = ft_strjoin((*hd).data_hd, "\n");
	}
	free((*hd).temp);
}

int	ft_last_main_hd(t_heredoc_data *hd, t_bash *cmd, t_list_export *exp,
		char *eof)
{
	char	*pf;
	char	*sr;

	(void)eof;
	pf = "/tmp/";
	sr = (*hd).eof;
	(*hd).arr = readline("> ");
	if (!(*hd).arr || ft_strcmp((*hd).arr, (*hd).eof) == 0)
	{
		(*hd).eof = ft_strjoin_bb(pf, sr);
		(*hd).eof = ft_strjoin((*hd).eof, ".tmp");
		(*hd).fd = open((*hd).eof, O_CREAT | O_RDWR | O_TRUNC, 0777);
		cmd->fd_heredoc = (*hd).fd;
		write((*hd).fd, (*hd).data_hd, ft_strlen((*hd).data_hd));
		free((*hd).data_hd);
		free((*hd).eof);
		free((*hd).arr);
		free(sr);
		return (0);
	}
	else if (ft_strcmp((*hd).arr, (*hd).eof) != 0)
		ft_sup_last_hd(hd, cmd, exp);
	free((*hd).arr);
	return (1);
}

void	ft_first_var_h(t_heredoc_data *hd, t_bash *cmd)
{
	(*hd).i++;
	free((*hd).eof);
	(*hd).eof = ft_strdup(cmd->file[(*hd).i]);
	(*hd).k++;
	free((*hd).arr);
}

int	ft_first_heredocs(t_heredoc_data *hd, t_bash *cmd, t_list_export *exp)
{
	(*hd).eof = ft_strdup(cmd->file[(*hd).i]);
	while (ft_strcmp(cmd->redirection[(*hd).i], "<<") == 0)
	{
		if ((*hd).k < ((*hd).j - 1))
		{
			while ((*hd).k < ((*hd).j - 1))
			{
				(*hd).arr = readline("> ");
				if (!(*hd).arr || ft_strcmp((*hd).arr, (*hd).eof) == 0)
				{
					ft_first_var_h(hd, cmd);
					break ;
				}
				free((*hd).arr);
			}
		}
		else if ((*hd).k == ((*hd).j - 1))
		{
			if (ft_last_main_hd(hd, cmd, exp, (*hd).eof) == 0)
				return (0);
		}
	}
	return (1);
}
