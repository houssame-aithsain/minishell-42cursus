/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:21:00 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	_ft_check_builtin_return_int_v2(t_bash *ptr)
{
	if (ft_strcmp(ptr->command, "export") == 0)
		return (1);
	else if (ft_strcmp(ptr->command, "exit") == 0)
		return (1);
	else if (ft_strcmp(ptr->command, "pwd") == 0)
		return (1);
	else if (ft_strcmp(ptr->command, "cd") == 0)
		return (1);
	else if (ft_strcmp(ptr->command, "unset") == 0)
		return (1);
	else if (ft_strcmp(ptr->command, "env") == 0)
		return (1);
	else if (ft_strcmp(ptr->command, "echo") == 0)
		return (1);
	return (0);
}

int	_ft_check_builtin_return_int_v3(t_bash *ptr)
{
	if (ft_strcmp(ptr->command, "export") == 0)
		return (1);
	else if (ft_strcmp(ptr->command, "exit") == 0)
		return (1);
	else if (ft_strcmp(ptr->command, "cd") == 0)
		return (1);
	else if (ft_strcmp(ptr->command, "unset") == 0)
		return (1);
	return (0);
}

int	__ft_check_heredoc(t_bash *cmd, t_list_export *exp)
{
	t_bash	*tmp;
	int		s;
	int		check;

	tmp = cmd;
	s = 0;
	check = 0;
	while (tmp)
	{
		if (check == 0)
		{
			s += ft_heredocs_counter(tmp->redirection);
			check = 1;
		}
		if (tmp->redirection && tmp->redirection[0])
			ft_heredoc(tmp, exp);
		tmp = tmp->link;
		check = 0;
	}
	return (s);
}

void	_ft_cond_one_pipe(t_bash *cmd, t_list_env **env, t_list_export **exp_ls,
		int *status)
{
	int	i;

	i = fork();
	if (i == 0)
	{
		ft_final_exec_sgl_cmd_without_fork(cmd, env, exp_ls);
		return ;
	}
	waitpid(i, status, 0);
	if (WIFEXITED(*status))
		t_e.exit_status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		t_e.exit_status = WTERMSIG(*status) + 128;
	_ft_update_exit_status(exp_ls, t_e.exit_status);
}

void	_ft_cond_two_pipe(t_bash *cmd, t_list_env **env, t_list_export **exp_ls,
		int *status)
{
	int	i;

	i = 0;
	if (cmd->redirection && cmd->redirection[0])
	{
		i = fork();
		if (i == 0)
		{
			ft_final_exec_sgl_cmd_without_fork(cmd, env, exp_ls);
			exit(0);
		}
		waitpid(i, status, 0);
		if (WIFEXITED(*status))
			t_e.exit_status = WEXITSTATUS(*status);
		else if (WIFSIGNALED(*status))
			t_e.exit_status = WTERMSIG(*status) + 128;
		_ft_update_exit_status(exp_ls, t_e.exit_status);
		if (_ft_check_builtin_return_int_v3(cmd))
			ft_check_builtins(cmd, env, exp_ls);
	}
	else
		ft_check_builtins(cmd, env, exp_ls);
	return ;
}
