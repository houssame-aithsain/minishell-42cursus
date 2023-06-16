/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 00:10:02 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*_ft_wrapper_cmds(t_bash *cmd, t_list_env **env, t_list_export **exp,
		int *k)
{
	char	*path_sp;

	path_sp = ft_check_access_cmd(cmd, env);
	ft_run_redir(cmd, *env, *exp);
	if (ft_check_builtins(cmd, env, exp) == 0)
	{
		_ft_update_exit_status(exp, 0);
		exit(0);
	}
	if ((cmd->command[0] == 1 && t_e.exit_status != 1) || (!path_sp && *k == 0))
		ft_error_handler(cmd, env, exp);
	else if ((!path_sp && *k != 0 && *k != 1))
	{
		write(2, "minishell: No such file or directory\n",
			ft_strlen("minishell: No such file or directory\n"));
		if (*k == 125)
		{
			_ft_update_exit_status(exp, 127);
			exit(127);
		}
		_ft_update_exit_status(exp, 1);
		exit(1);
	}
	return (path_sp);
}

void	_ft_init_fork_data(t_fork_data *sfd, t_bash *cmd, t_list_env **env,
		t_list_export **exp)
{
	(*sfd).i = 0;
	(*sfd).j = 0;
	(*sfd).k = ft_check_slash_dot(cmd, *env);
	(*sfd).path_sp = _ft_wrapper_cmds(cmd, env, exp, &((*sfd).k));
	(*sfd).args = malloc(sizeof(char *) * 3);
	(*sfd).env_arr = NULL;
}

int	ft_final_exec_sgl_cmd_without_fork(t_bash *cmd, t_list_env **env,
		t_list_export **exp)
{
	t_fork_data	sfd;

	_ft_init_fork_data(&sfd, cmd, env, exp);
	if (sfd.path_sp || sfd.k == 1)
	{
		sfd.args[sfd.j] = cmd->command;
		sfd.j = 1;
		while (cmd->arg[sfd.i])
			sfd.args[sfd.j++] = cmd->arg[sfd.i++];
		sfd.args[sfd.j] = NULL;
		sfd.env_arr = ft_lst_to_array(*env);
		if (sfd.k == 1)
			sfd.path_sp = cmd->command;
		if (execve(sfd.path_sp, sfd.args, sfd.env_arr) == -1)
		{
			if (cmd->command && sfd.k == 1)
				printf("minishell: %s: is a directory\n", cmd->command);
			_ft_update_exit_status(exp, 127);
			exit(127);
		}
	}
	return (1);
}

void	closing_fd(t_bash *cmd, int number_of_pipes, int **fd)
{
	int	j;

	j = 0;
	(void)cmd;
	while (j < number_of_pipes)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
}

int	_ft_check_builtin_return_int(t_bash *ptr)
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
	return (0);
}
