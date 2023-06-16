/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirv2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:12:48 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	_ft_second_condition_in(t_bash *cmd, t_redir_in *ins)
{
	int	ss;

	(void)cmd;
	ss = access((*ins).last_c->file[(*ins).last], R_OK);
	if (ss == 0)
	{
		(*ins).ds = open((*ins).last_c->file[(*ins).last], O_RDONLY);
		if ((*ins).ds == -1)
			return (-400);
		return ((*ins).ds);
	}
	else
	{
		write(2, "minishell: Permission denied\n",
			ft_strlen("minishell: Permission denied\n"));
		t_e.exit_status = 1;
		exit(1);
		return (-9090);
	}
	return (1);
}

char	*ft_read_hd_fd(t_bash *cmd, t_redir_in *ins)
{
	char	*pf;

	(void)cmd;
	pf = "/tmp/";
	(*ins).ss = ft_strjoin_bb(pf, (*ins).last_c->file[(*ins).last]);
	(*ins).ss = ft_strjoin((*ins).ss, ".tmp");
	return ((*ins).ss);
}

int	_ft_check_last_in(t_bash *cmd)
{
	t_redir_in	ins;

	(void)cmd;
	ft_init_redir_in(cmd, &ins);
	while (ins.last_c->redirection[ins.i])
	{
		ins.p = _ft_first_condition_in(cmd, &ins);
		if (ins.p != 1)
			return (ins.p);
		ins.i++;
	}
	if (ins.last_c->redirection[ins.last]
		&& ft_strcmp(ins.last_c->redirection[ins.last], "<") == 0)
	{
		ins.p = _ft_second_condition_in(cmd, &ins);
		if (ins.p != 1)
			return (ins.p);
	}
	if (ins.last_c->redirection[ins.last]
		&& ft_strcmp(ins.last_c->redirection[ins.last], "<<") == 0)
	{
		ins.ss = ft_read_hd_fd(cmd, &ins);
		return (open(ins.ss, O_RDONLY));
	}
	return (-404);
}

int	_ft_first_cond_out(t_bash *cmd, t_redir_out *out)
{
	(void)cmd;
	if (((*out).last_c->file[(*out).i] && (*out).last_c->file[(*out).i][0] == 4)
		|| (*out).last_c->error == 10)
		return (-18);
	if (ft_strcmp((*out).last_c->redirection[(*out).i], ">") == 0)
	{
		(*out).ds = open((*out).last_c->file[(*out).i],
				O_CREAT | O_RDWR | O_TRUNC, 0777);
		if ((*out).ds == -1)
		{
			write(2, "minishell: Permission denied\n",
				ft_strlen("minishell: Permission denied\n"));
			t_e.exit_status = 1;
			exit(1);
			return (-9090);
		}
	}
	return (1);
}

void	_ft_errors_redir(t_main_redir *mr)
{
	if ((*mr).first_in == -400 && (*mr).last_out == -404)
	{
		write(2, "minishell: ambiguous redirect\n",
			ft_strlen("minishell: ambiguous redirect\n"));
		t_e.exit_status = 1;
		exit(1);
	}
	else if ((*mr).first_in == -404 && (*mr).last_out == -1)
	{
		write(2, "minishell: ambiguous redirect\n",
			ft_strlen("minishell: ambiguous redirect\n"));
		t_e.exit_status = 1;
		exit(1);
	}
	else if ((*mr).first_in > 0)
	{
		dup2((*mr).first_in, STDIN_FILENO);
		close((*mr).first_in);
	}
	if ((*mr).last_out > 0)
	{
		dup2((*mr).last_out, STDOUT_FILENO);
		close((*mr).last_out);
	}
}
