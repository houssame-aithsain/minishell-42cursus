/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:46:17 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_run_redir(t_bash *cmd, t_list_env *env, t_list_export *exp)
{
	t_main_redir	mr;

	(void)env;
	(void)exp;
	ft_init_main_redir_vars(&mr, cmd);
	if (mr.first_in == -18 || mr.last_out == -18)
	{
		write(2, "minishell: ambiguous redirect\n",
			ft_strlen("minishell: ambiguous redirect\n"));
		t_e.exit_status = 1;
		exit(1);
	}
	else if (mr.first_in == -404 && mr.last_out == -404)
		return ;
	else if (mr.first_in == -400)
	{
		write(2, "minishell: No such file or directory\n",
			ft_strlen("minishell: No such file or directory\n"));
		t_e.exit_status = 1;
		exit(1);
	}
	else
		_ft_errors_redir(&mr);
}

int	_ft_check_access_infile(char *red, char *file)
{
	if (ft_strcmp(red, "<") == 0)
	{
		if (access(file, R_OK | F_OK) == -1)
			return (-1);
	}
	return (-4);
}
