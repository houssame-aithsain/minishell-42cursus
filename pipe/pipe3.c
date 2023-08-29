/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:20:29 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	_ft_init_pipes(t_pipe_s *sp, t_list_env **env, t_bash *cmd)
{
	(*sp).pid = malloc(sizeof(int) * ((*sp).number_of_pipes + 1));
	(*sp).fd = malloc(sizeof(int *) * ((*sp).number_of_pipes));
	while ((*sp).i < (*sp).number_of_pipes)
		(*sp).fd[(*sp).i++] = malloc(sizeof(int) * 2);
	(*sp).i = 0;
	while ((*sp).i < (*sp).number_of_pipes)
		pipe((*sp).fd[(*sp).i++]);
	(*sp).i = 0;
	(*sp).tmp = cmd;
	(*sp).e = ft_lst_to_array(*env);
}

void	_ft_n_pipes_handler(t_pipe_s *sp, t_list_env **env, t_bash *cmd,
		t_list_export **exp_ls)
{
	while ((*sp).number_of_pipes != 0 && (*sp).i <= (*sp).number_of_pipes
		&& cmd)
	{
		(*sp).pid[(*sp).i] = fork();
		if ((*sp).pid[(*sp).i] == 0)
		{
			if ((*sp).i == 0)
				dup2((*sp).fd[(*sp).i][1], STDOUT_FILENO);
			else if ((*sp).i == (*sp).number_of_pipes)
				dup2((*sp).fd[(*sp).i - 1][0], STDIN_FILENO);
			else
			{
				dup2((*sp).fd[(*sp).i - 1][0], STDIN_FILENO);
				dup2((*sp).fd[(*sp).i][1], STDOUT_FILENO);
			}
			closing_fd(cmd, (*sp).number_of_pipes, (*sp).fd);
			ft_final_exec_sgl_cmd_without_fork(cmd, env, exp_ls);
		}
		(*sp).i++;
		cmd = cmd->link;
	}
	closing_fd(cmd, (*sp).number_of_pipes, (*sp).fd);
}

void	_ft_wait_childs_ndexit(t_pipe_s *sp, t_list_env **env, t_bash *cmd,
		t_list_export **exp_ls)
{
	(*sp).i = 0;
	(void)cmd;
	(void)env;
	while ((*sp).i <= (*sp).number_of_pipes)
	{
		waitpid((*sp).pid[(*sp).i++], &(*sp).status, 0);
		t_e.exit_status = (*sp).status >> 8;
		_ft_update_exit_status(exp_ls, t_e.exit_status);
	}
}

void	_ft_free_all_for_pipes(t_pipe_s *sp)
{
	int	s;

	s = 0;
	if ((*sp).pid)
		free((*sp).pid);
	if ((*sp).e)
		free((*sp).e);
	if ((*sp).fd)
	{
		while (s < (*sp).number_of_pipes)
		{
			free((*sp).fd[s]);
			s++;
		}
		free((*sp).fd);
	}
}

void	n_pipe(t_bash *cmd, t_list_env **env, t_list_export **exp_ls)
{
	t_pipe_s	sp;

	_ft_pipe_init_vars(&sp);
	if (!cmd)
		return ;
	sp.number_of_pipes = ft_count_cmds_exp(cmd) - 1;
	if (sp.number_of_pipes == 0 && _ft_check_builtin_return_int(cmd) == 0)
		_ft_cond_one_pipe(cmd, env, exp_ls, &sp.status);
	else if (sp.number_of_pipes == 0 && _ft_check_builtin_return_int(cmd) == 1)
		_ft_cond_two_pipe(cmd, env, exp_ls, &sp.status);
	else
	{
		_ft_init_pipes(&sp, env, cmd);
		_ft_n_pipes_handler(&sp, env, cmd, exp_ls);
		_ft_wait_childs_ndexit(&sp, env, cmd, exp_ls);
		_ft_free_all_for_pipes(&sp);
	}
}
