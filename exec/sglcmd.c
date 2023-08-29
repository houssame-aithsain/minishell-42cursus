/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sglcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:42:26 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_getpath_cmd(t_list_env **env)
{
	char		**path_splited;
	t_list_env	*env_ls;
	int			j;

	j = 0;
	path_splited = NULL;
	env_ls = *env;
	while (env_ls)
	{
		if (ft_strcmp(env_ls->key, "PATH") == 0)
		{
			while (env_ls->content[j] != '=')
				j++;
			path_splited = ft_split(&env_ls->content[j + 1], ':');
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
	free(arg);
}

char	*ft_check_access_cmd(t_bash *cmd, t_list_env **env)
{
	char	**path_sp;
	char	*sgl_path;
	int		i;

	i = 0;
	path_sp = ft_getpath_cmd(env);
	if (!path_sp)
		return (NULL);
	sgl_path = NULL;
	while (path_sp && path_sp[i])
	{
		path_sp[i] = ft_strjoin(path_sp[i], "/");
		path_sp[i] = ft_strjoin(path_sp[i], cmd->command);
		if (access(path_sp[i], X_OK | F_OK) == 0)
		{
			sgl_path = ft_strdup(path_sp[i]);
			ft_free_args(path_sp);
			return (sgl_path);
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
