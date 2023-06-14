/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 00:10:02 by gothmane          #+#    #+#             */
/*   Updated: 2023/06/12 15:07:17 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int _ft_check_if_redir(t_bash *cmd)
{
	while (cmd)
	{
		if (cmd->redirection[0])
			return (1);
		cmd = cmd->link;
	}
	return (0);
}

t_bash *_ft_push_me_to_redir(t_bash *cmd)
{
	while (cmd)
	{
		if (cmd->redirection[0])
			return (cmd);
		cmd = cmd->link;
	}
	return (0);
}

int ft_find_key__v22(t_list_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "HOME") == 0)
			return (1);
		env = env->next;
	}
	return (0);
}
int	ft_help_check_builtin(t_bash *ptr, t_list_env **env_ls, t_list_export **exp_ls)
{
	if (ft_strcmp(ptr->command, "cd") == 0)
	{
		if (!ptr->arg[0] && ft_find_key__v22(*env_ls) == 0)
		{
			printf("minishell: cd: HOME not set\n");
			return (1);
		}
		ft_cd(ptr->arg[0], env_ls);
	}
	else if (ft_strcmp(ptr->command, "unset") == 0)
		ft_unset(env_ls, exp_ls, ptr->arg);
	else if (ft_strcmp(ptr->command, "env") == 0)
		ft_print_lst_env(*env_ls);
	else if (ft_strcmp(ptr->command, "exit") == 0)
		ft_exit(ptr);
	else
		return (1);
	return (0);
}

int ft_check_builtins(t_bash *ptr, t_list_env **env_ls, t_list_export **exp_ls)
{
	int	k;
	
	k = ft_help_check_builtin(ptr, env_ls, exp_ls);
	if (k == 0)
		return (1);
	else if (ft_strcmp(ptr->command, "export") == 0)
	{
		ft_export(exp_ls, ptr->arg, env_ls);
		if (!ptr->arg[0])
			ft_print_lst(*exp_ls);
	}
	else if (ft_strcmp(ptr->command, "echo") == 0)
		ft_echo(ptr->arg);
	else if (ft_strcmp(ptr->command, "pwd") == 0)
		ft_pwd();
	else
		return (1);
	return (0);
}

int ft_find_occur(char *cmd, char c)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int ft_check_slash_dot(t_bash *cmd, t_list_env *env)
{
	int i;

	i = 0;
	if (ft_find_occur(cmd->command, '/') == 1)
	{
		if (access(cmd->command, X_OK | F_OK) == 0)
			return (1);
		else
			return (125);
	}
	return (0);
}

int ft_find_key__(t_list_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	_ft_update_exit_status(t_bash *cmd, t_list_env **env, t_list_export **exp, int exit_s)
{
	char	*qst;
	char	*str_es;
	
	qst = ft_strdup("?=");
	exit_status = exit_s;
	str_es = ft_itoa(exit_status);
	// printf("exit_status = %d\n",exit_status);
	ft_delete_node(exp, "?");
	qst = ft_strjoin(qst, str_es);
	ft_lstadd_back_export(exp, ft_lstnew_mod(qst));
	// update ?=
	free(str_es);
	free(qst);
	// end update ?=
	// exit(exit_s);
}

void	ft_error_handler(t_bash *cmd, t_list_env **env, t_list_export **exp)
{
	if (ft_find_key__(*env) == 1)
	{
		write(2, "minishell: command not found\n", ft_strlen("minishell: command not found\n"));
		_ft_update_exit_status(cmd, env, exp, 127);
		exit(127);
	}
	else if (ft_find_key__(*env) == 0 && _ft_check_builtin_return_int_v2(cmd) == 0)
	{
		write(2, "minishell: No such file or directory\n", ft_strlen("minishell: No such file or directory\n"));
		_ft_update_exit_status(cmd, env, exp, 127);
		exit(127);
	}
}
char	*_ft_wrapper_cmds(t_bash *cmd, t_list_env **env, t_list_export **exp, int k)
{
	char *path_sp;
	
	path_sp = ft_check_access_cmd(cmd, *env);
	ft_run_redir(cmd, *env, *exp);
	if (ft_check_builtins(cmd, env, exp) == 0)
	{
		exit_status = 0;
		_ft_update_exit_status(cmd, env, exp, 0);
		exit(0);
	}
	if ((cmd->command[0] == 1 && exit_status != 1) || (!path_sp && k == 0))
		ft_error_handler(cmd, env, exp);
	else if ((!path_sp && k != 0 && k != 1))
	{
		write(2, "minishell: No such file or directory\n", ft_strlen("minishell: No such file or directory\n"));
		_ft_update_exit_status(cmd, env, exp, 1);
		exit(1);
	}
	return (path_sp);
}

int ft_final_exec_sgl_cmd_without_fork(t_bash *cmd, t_list_env **env, t_list_export **exp)
{
	char *path_sp;
	char **args;
	int i;
	int j;
	char **env_arr;
	int k;
	
	i = 0;
	j = 0;
	k = ft_check_slash_dot(cmd, *env);
	path_sp = _ft_wrapper_cmds(cmd, env, exp, k);
	args = malloc(sizeof(char *) * 3);
	env_arr = NULL;
	if (path_sp || k == 1)
	{
		args[j] = cmd->command;
		j = 1;
		while (cmd->arg[i])
			args[j++] = cmd->arg[i++];
		args[j] = NULL;
		env_arr = ft_lst_to_array(*env);
		if (k == 1)
			path_sp = cmd->command;
		if (execve(path_sp, args, env_arr) == -1)
		{
			if (cmd->command && k == 1)
				printf("minishell: %s: is a directory\n", cmd->command);
			_ft_update_exit_status(cmd, env, exp, 127);
			exit(127);
		}
	}
	return (1);
}

void closing_fd(t_bash *cmd, int number_of_pipes, int **fd)
{
	int j;

	j = 0;
	while (j < number_of_pipes)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
}

int _ft_check_builtin_return_int(t_bash *ptr)
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

int _ft_check_builtin_return_int_v2(t_bash *ptr)
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

int _ft_check_builtin_return_int_v3(t_bash *ptr)
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

int __ft_check_heredoc(t_bash *cmd, t_list_export *exp)
{
	t_bash *tmp;
	int i;
	// char	**result;

	i = 0;
	tmp = cmd;
	int s = 0;
	int check = 0;
	
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
	return (0);
}

void n_pipe(t_bash *cmd, t_list_env **env, t_list_export **exp_ls)
{
	int i;
	int *pid;
	int **fd;
	int number_of_pipes;
	int status = 0;

	i = 0;
	if (!cmd)
		return;
	__ft_check_heredoc(cmd, *exp_ls);
	number_of_pipes = ft_count_cmds_exp(cmd) - 1;
	if (number_of_pipes == 0 && _ft_check_builtin_return_int(cmd) == 0)
	{
		i = fork();
		if (i == 0)
		{
			ft_final_exec_sgl_cmd_without_fork(cmd, env, exp_ls);
			return;
		}
		waitpid(i, &status, 0);
		exit_status = status >> 8;
		_ft_update_exit_status(cmd, env, exp_ls, exit_status);
		// exit(exit_status);
		// _ft_update_exit_status(cmd, env, exp_ls, exit_status);
		// update ?=
		// ft_delete_node(exp_ls, "?");
		// char *qst = ft_strdup("?=");
		// char *str_es = ft_itoa(exit_status);
		// qst = ft_strjoin(qst, str_es);
		// free(str_es);
		// ft_lstadd_back_export(exp_ls, ft_lstnew_mod(qst));
		// free(qst);
		// end update ?=
	}
	else if (number_of_pipes == 0 && _ft_check_builtin_return_int(cmd) == 1)
	{
		if (cmd->redirection && cmd->redirection[0])
		{
			i = fork();
			if (i == 0)
			{
				ft_final_exec_sgl_cmd_without_fork(cmd, env, exp_ls);
				exit(0);
			}
			waitpid(i, &status, 0);
			exit_status = status >> 8;
			_ft_update_exit_status(cmd, env, exp_ls, exit_status);
			// update ?=
			// ft_delete_node(exp_ls, "?");
			// char *qst = ft_strdup("?=");
			// char *str_es = ft_itoa(exit_status);
			// qst = ft_strjoin(qst, str_es);
			// free(str_es);
			// ft_lstadd_back_export(exp_ls, ft_lstnew_mod(qst));
			// free(qst);
			// end update ?=
			if (_ft_check_builtin_return_int_v3(cmd))
				ft_check_builtins(cmd, env, exp_ls);
		}
		else
			ft_check_builtins(cmd, env, exp_ls);
		return;
	}
	else
	{
		pid = malloc(sizeof(int) * (number_of_pipes + 1));
		fd = malloc(sizeof(int *) * (number_of_pipes));
		while (i < number_of_pipes)
			fd[i++] = malloc(sizeof(int) * 2);
		i = 0;

		while (i < number_of_pipes)
			pipe(fd[i++]);
		i = 0;
		int j;
		t_bash *tmp = cmd;
		char **e = ft_lst_to_array(*env);
		while (number_of_pipes != 0 && i <= number_of_pipes && cmd)
		{
			pid[i] = fork();
			if (pid[i] == 0)
			{
				if (i == 0)
				{
					dup2(fd[i][1], STDOUT_FILENO);
					closing_fd(cmd, number_of_pipes, fd);
					ft_final_exec_sgl_cmd_without_fork(cmd, env, exp_ls);
				}
				else if (i == number_of_pipes)
				{
					dup2(fd[i - 1][0], STDIN_FILENO);
					closing_fd(cmd, number_of_pipes, fd);
					ft_final_exec_sgl_cmd_without_fork(cmd, env, exp_ls);
				}
				else
				{
					dup2(fd[i - 1][0], STDIN_FILENO);
					dup2(fd[i][1], STDOUT_FILENO);
					closing_fd(cmd, number_of_pipes, fd);
					ft_final_exec_sgl_cmd_without_fork(cmd, env, exp_ls);
				}
			}
			i++;
			cmd = cmd->link;
		}
		closing_fd(cmd, number_of_pipes, fd);
		i = 0;
		while (i <= number_of_pipes)
		{
			waitpid(pid[i++], &status, 0);
			exit_status = status >> 8;
			_ft_update_exit_status(cmd, env, exp_ls, exit_status);
		}
		if (pid)
			free(pid);
		int s = 0;
		int se;
		if (e)
			se = ft_count_2d(e);
		if (e)
			free(e);
		s = 0;
		if (fd)
		{
			while (s < number_of_pipes)
			{
				free(fd[s]);
				s++;
			}
			free(fd);
		}
	}
}
