/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:41:40 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_access_red(char *file)
{
	int	r;

	r = access(file, F_OK | R_OK);
	if (r == 0)
		return (1);
	else
		return (-1);
}

void	ft_init_redir_in(t_bash *cmd, t_redir_in *ins)
{
	(*ins).i = 0;
	(*ins).ds = 0;
	(*ins).last = 0;
	(*ins).last_c = cmd;
	(*ins).p = 0;
	(*ins).ss = NULL;
}

void	ft_init_main_redir_vars(t_main_redir *mr, t_bash *cmd)
{
	(*mr).s = -1;
	(*mr).k = -1;
	(*mr).here_doc_string = NULL;
	(*mr).first_in = _ft_check_last_in(cmd);
	(*mr).last_out = _ft_check_last_out(cmd);
}

int	ft_check_cmd(t_bash *cmd, t_list_env *env)
{
	char	*path_sp;
	int		cc;

	cc = _ft_check_builtin_return_int(cmd);
	path_sp = ft_check_access_cmd(cmd, &env);
	if (!path_sp && ft_check_slash_dot(cmd, env) != 1 && cc != 1)
		return (0);
	return (1);
}

int	ft_count_redir_type(t_bash *cmd, char *c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (cmd->redirection[i])
	{
		if (ft_strncmp(cmd->redirection[i], c, 2) == 0)
			j++;
		i++;
	}
	return (j);
}
