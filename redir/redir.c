/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:29:13 by gothmane          #+#    #+#             */
/*   Updated: 2023/05/28 21:48:43 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_file_counter_redir(t_bash *cmd)
{
	t_bash *cc_c;
	int		i;

	i = 0;
	cc_c = cmd;
	while (cc_c)
	{
		if (cmd->file)
			i++;
		cc_c = cc_c->link;
	}
	return (i);
}

int	ft_open_files(t_bash *cmd)
{
	int		i;
	char	*files[5];
	int		file_counter;
	int		redir_counter;
	t_bash	*cmd_c;
	int		*files_fd;
	// char	**files;
	
	i = 0;
	cmd_c = cmd;
	files[0] = "out";
	files[1] = "file1";
	files[2] = "out2";
	files[3] = "file3";
	files[4] = NULL;
	// file_counter = ft_file_counter_redir(cmd);
	file_counter = 4;
	files_fd = NULL;
	if (file_counter > 0 && cmd_c)
	{
		files_fd = malloc(sizeof(int) * file_counter);
		while (files[i])
		{
			// printf("file = %s\n", files[i]);
			files_fd[i] = open(files[i], O_RDWR, NULL);
			if (files_fd[i] == -1)
				files_fd[i] = open(files[i], O_RDWR | O_CREAT, 0664);
			// cmd_c = cmd_c->link;
			i++;
		}
	}
	return (files_fd[--i]);
}

void	ft_redir_ex(t_bash *cmd, t_list_env *env)
{
	int	fd;

	fd = ft_open_files(cmd);
	printf("%d\n", fd);
	
	// ft_final_exec_sgl_cmd(cmd, env);
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
		i = fork();
		if (i == 0)
		{
			dup2(fd, STDOUT_FILENO);
			env_arr = ft_lst_to_array(env);
			execve(path_sp, args, env_arr);
		}
		wait(NULL);
		free(path_sp);
		// ft_free_args(args);
		// return (args);
	}
}