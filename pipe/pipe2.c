/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:19:54 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_find_occur(char *cmd, char c)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_slash_dot(t_bash *cmd, t_list_env *env)
{
	(void)env;
	if (ft_find_occur(cmd->command, '/') == 1)
	{
		if (access(cmd->command, X_OK | F_OK) == 0)
			return (1);
		else
			return (125);
	}
	return (0);
}

int	ft_find_key__(t_list_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	_ft_update_exit_status(t_list_export **exp, int exit_s)
{
	char	*qst;
	char	*str_es;

	qst = ft_strdup("?=");
	t_e.exit_status = exit_s;
	str_es = ft_itoa(t_e.exit_status);
	ft_delete_node(exp, "?");
	qst = ft_strjoin(qst, str_es);
	ft_lstadd_back_export(exp, ft_lstnew_mod(qst));
	free(str_es);
	free(qst);
}

void	ft_error_handler(t_bash *cmd, t_list_env **env, t_list_export **exp)
{
	if (ft_find_key__(*env) == 1)
	{
		write(2, "minishell: command not found\n",
			ft_strlen("minishell: command not found\n"));
		_ft_update_exit_status(exp, 127);
		exit(127);
	}
	else if (ft_find_key__(*env) == 0
		&& _ft_check_builtin_return_int_v2(cmd) == 0)
	{
		write(2, "minishell: No such file or directory\n",
			ft_strlen("minishell: No such file or directory\n"));
		_ft_update_exit_status(exp, 127);
		exit(127);
	}
}
