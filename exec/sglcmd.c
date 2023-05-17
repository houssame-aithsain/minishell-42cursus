/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sglcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:42:26 by gothmane          #+#    #+#             */
/*   Updated: 2023/05/16 01:16:32 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_getpath_cmd(t_list_env *env)
{
	int			i;
	char		**path_splited;
	t_list_env	*env_ls;

	i = 0;
	path_splited = NULL;
	env_ls = env;
	while (env_ls)
	{
		if (ft_strcmp(env_ls->key, "PATH") == 0)
		{
			path_splited = ft_split(env_ls->value, ':');
			return (path_splited);
		}
		env_ls = env_ls->next;
	}
	return (NULL);
}

void	ft_free_args(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
}

char	*ft_check_access_cmd(t_bash *cmd, t_list_env *env)
{
	char	**path_sp;
	char	*sgl_path;
	int		i;

	i = 0;
	path_sp = ft_getpath_cmd(env);
	sgl_path = NULL;
	while (path_sp && path_sp[i])
	{
		path_sp[i] = ft_strjoin(path_sp[i], "/");
		path_sp[i] = ft_strjoin(path_sp[i], cmd->command);
		if (access(path_sp[i], X_OK | F_OK) == 0)
		{
			sgl_path = ft_strdup(path_sp[i]);
			ft_free_args(path_sp);
			return(sgl_path);
		}
		i++;
	}
	ft_free_args(path_sp);
	return (0);
}

int	ft_count_cmds(t_bash *cmd)
{
	int	i;

	i = 0;
	while (cmd->arg[i])
		i++;
	return (i);
}

int	ft_lstsize_env(t_list_env *lst)
{
	int		count;
	t_list_env	*n;

	count = 0;
	n = NULL;
	if (!lst)
		return (0);
	n = lst;
	while (n)
	{
		count++;
		n = n->next;
	}
	return (count);
}


char	**ft_lst_to_array(t_list_env *env)
{
	t_list_env	*env_ls;
	char		**new_ls;
	int			i;

	env_ls = env;
	new_ls = malloc(sizeof(char *) * (ft_lstsize_env(env) + 1));
	i = 0;
	while (env_ls)
	{
		new_ls[i++] = env_ls->content;
		env_ls = env_ls->next;
	}
	return (new_ls);
}

char	**ft_final_exec_sgl_cmd(t_bash *cmd, t_list_env *env)
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
		i = fork();
		if (i == 0)
		{
			env_arr = ft_lst_to_array(env);
			execve(path_sp, args, env_arr);
		}
		wait(NULL);
		free(path_sp);
		// ft_free_args(args);
		// return (args);
	}
	return (0);
}