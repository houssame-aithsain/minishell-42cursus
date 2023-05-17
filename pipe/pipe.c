/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 00:10:02 by gothmane          #+#    #+#             */
/*   Updated: 2023/05/16 19:36:18 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	**ft_final_exec_sgl_cmd_without_fork(t_bash *cmd, t_list_env *env)
{
	char	*path_sp;
	char	**args;
	int		i;
	char	**env_arr;

	i = 0;
	path_sp = ft_check_access_cmd(cmd, env);
	args = malloc(sizeof(char *) * (ft_count_cmds(cmd) + 2));
	env_arr = NULL;
	if (path_sp)
	{
		args[0] = cmd->command;
		while (cmd->arg[i])
		{
			args[i + 1] = cmd->arg[i];
			i++;
		}
		args[i + 1] = NULL;
		env_arr = ft_lst_to_array(env);
		execve(path_sp, args, env_arr);
		free(path_sp);
		// ft_free_args(args);
		// return (args);
	}
	return (0);
}

void	ft_piping_bash(t_bash *cmd, t_list_env *env)
{
	int	pid;
	int	pid2;
	int	fd[2];

	if (pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		ft_final_exec_sgl_cmd_without_fork(cmd, env);
		// exit(0);
	}
	if (cmd->link)
		cmd = cmd->link;
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		ft_final_exec_sgl_cmd_without_fork(cmd, env);
		// exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid2, NULL, 0);
	waitpid(pid, NULL, 0);
	// exit(0);
}