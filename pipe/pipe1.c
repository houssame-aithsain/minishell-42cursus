/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:19:26 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	_ft_check_if_redir(t_bash *cmd)
{
	while (cmd)
	{
		if (cmd->redirection[0])
			return (1);
		cmd = cmd->link;
	}
	return (0);
}

t_bash	*_ft_push_me_to_redir(t_bash *cmd)
{
	while (cmd)
	{
		if (cmd->redirection[0])
			return (cmd);
		cmd = cmd->link;
	}
	return (0);
}

int	ft_find_key__v22(t_list_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "HOME") == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

int	ft_help_check_builtin(t_bash *ptr, t_list_env **env_ls,
		t_list_export **exp_ls)
{
	if (ft_strcmp(ptr->command, "cd") == 0)
	{
		if (!ptr->arg[0] && ft_find_key__v22(*env_ls) == 0)
		{
			printf("minishell: cd: HOME not set\n");
			return (1);
		}
		ft_cd(ptr->arg[0], env_ls, exp_ls);
	}
	else if (ft_strcmp(ptr->command, "unset") == 0)
		ft_unset(env_ls, exp_ls, ptr->arg);
	else if (ft_strcmp(ptr->command, "env") == 0)
		ft_print_lst_env(*env_ls);
	else if (ft_strcmp(ptr->command, "exit") == 0)
	{
		write(1, "exit\n", 5);
		ft_exit(ptr);
	}
	else
		return (1);
	return (0);
}

int	ft_check_builtins(t_bash *ptr, t_list_env **env_ls, t_list_export **exp_ls)
{
	int	k;

	k = ft_help_check_builtin(ptr, env_ls, exp_ls);
	if (k == 0)
		return (0);
	else if (ft_strcmp(ptr->command, "export") == 0)
	{
		ft_export(exp_ls, ptr->arg, env_ls);
		if (!ptr->arg[0])
			ft_print_lst(*exp_ls);
	}
	else if (ft_strcmp(ptr->command, "echo") == 0)
		ft_echo(ptr->arg);
	else if (ft_strcmp(ptr->command, "pwd") == 0)
		ft_pwd(exp_ls);
	else
		return (1);
	return (0);
}
