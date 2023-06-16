/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:57:54 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_wrapped_free_for_delete_env(t_list_env *temp)
{
	if (temp->key)
		free(temp->key);
	if (temp->value)
		free(temp->value);
	if (temp->content)
		free(temp->content);
	if (temp)
		free(temp);
}

void	ft_delete_node_env_for_cd(t_list_env **head, char *key)
{
	t_list_env	*temp;
	t_list_env	*current;

	current = *head;
	if (ft_strcmp((*head)->key, key) == 0)
	{
		temp = *head;
		*head = (*head)->next;
		ft_wrapped_free_for_delete_env(temp);
	}
	else
	{
		while (current->next != NULL)
		{
			if (ft_strcmp(current->next->key, key) == 0)
			{
				temp = current->next;
				current->next = current->next->next;
				ft_wrapped_free_for_delete_env(temp);
				break ;
			}
			else
				current = current->next;
		}
	}
}

void	ft_replace_pwd(t_list_env **env_ls)
{
	char	*oldpwd;
	char	*pwd;
	char	*buffer;
	char	*value;

	value = ft_getval_env("PWD", *env_ls);
	if (!value)
		return ;
	buffer = getcwd(NULL, 0);
	oldpwd = ft_strdup("OLDPWD=");
	oldpwd = ft_strjoin(oldpwd, value);
	ft_delete_node_env_for_cd(env_ls, "OLDPWD");
	ft_lstadd_back_env(env_ls, ft_lstnew_mod_env(oldpwd));
	ft_delete_node_env(env_ls, "PWD");
	pwd = ft_strdup("PWD=");
	if (buffer)
		pwd = ft_strjoin(pwd, buffer);
	ft_lstadd_back_env(env_ls, ft_lstnew_mod_env(pwd));
	free(oldpwd);
	free(buffer);
	free(pwd);
}

void	ft_cd(char *path, t_list_env **env_ls, t_list_export **exp_ls)
{
	int		err;

	err = 0;
	if (!path || ft_strncmp(path, "~", 1) == 0)
		err = chdir(getenv("HOME"));
	else
	{
		err = chdir(path);
		if (err != -1)
		{
			ft_replace_pwd(env_ls);
			t_e.exit_status = 0;
			_ft_update_exit_status(exp_ls, t_e.exit_status);
		}
	}
	if (err == -1)
		_ft_cd_sup_err(env_ls, exp_ls);
}

int	ft_pwd(t_list_export **exp_ls)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (buffer)
	{
		printf("%s\n", buffer);
		free(buffer);
		t_e.exit_status = 0;
		_ft_update_exit_status(exp_ls, t_e.exit_status);
		return (1);
	}
	free(buffer);
	return (0);
}
