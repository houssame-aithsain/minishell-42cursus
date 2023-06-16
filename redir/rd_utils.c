/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:34:08 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/15 16:32:20 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_file_counter_redir(t_bash *cmd)
{
	t_bash	*cc_c;
	int		i;

	i = 0;
	cc_c = cmd;
	while (cc_c)
	{
		if (cmd->file)
			i++;
		cc_c = cc_c->link;
	}
	return (i);
}

void	_ft_init_out_var(t_redir_out *out, t_bash *cmd)
{
	(*out).i = 0;
	(*out).ds = -404;
	(*out).last_c = cmd;
	(*out).hold_a = 0;
	(*out).hold_b = 0;
}

int	_ft_second_cond_out(t_bash *cmd, t_redir_out *out)
{
	(void)cmd;
	(void)out;
	write(2, "minishell: Permission denied\n",
		ft_strlen("minishell: Permission denied\n"));
	t_e.exit_status = 1;
	exit(1);
	return (-9090);
}

int	ft_break_in_acc(t_redir_out *out)
{
	if (_ft_check_access_infile((*out).last_c->redirection[(*out).i],
			(*out).last_c->file[(*out).i]) == -1)
		return (1);
	else
		return (0);
}

int	_ft_check_last_out(t_bash *cmd)
{
	t_redir_out	out;

	_ft_init_out_var(&out, cmd);
	while (out.last_c->redirection[out.i])
	{
		if (ft_break_in_acc(&out) == 1)
			break ;
		else if (ft_strcmp(out.last_c->redirection[out.i], ">") == 0
			|| ft_strcmp(out.last_c->redirection[out.i], ">>") == 0)
		{
			out.hold_a = _ft_first_cond_out(cmd, &out);
			if (out.hold_a != 1)
				return (out.hold_a);
			else if (ft_strcmp(out.last_c->redirection[out.i], ">>") == 0)
			{
				out.ds = open(out.last_c->file[out.i],
						O_CREAT | O_RDWR | O_APPEND, 0777);
				if (out.ds == -1)
					_ft_second_cond_out(cmd, &out);
			}
		}
		out.i++;
	}
	return (out.ds);
}
