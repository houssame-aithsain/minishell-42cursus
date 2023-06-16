/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:53:07 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(char **env)
{
	int	i;

	i = -1;
	while (++i < ft_count_2d(env))
		printf("%s\n", env[i]);
}

int	_ft_exit_v(t_bash *ptr, int size_c)
{
	int	j;

	j = 0;
	while (ptr->arg[0][j])
	{
		if (ft_isalpha(ptr->arg[0][j]) == 1)
		{
			printf("minishell: exit: %s: numeric argument required\n",
				ptr->arg[0]);
			exit(255);
		}
		if (size_c > 1)
		{
			printf("minishell: exit: too many arguments\n");
			t_e.exit_status = 1;
			return (1);
		}
		j++;
	}
	return (0);
}

int	_ft_exit_check_arg(t_bash *ptr)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (ptr->arg[i])
	{
		j = 0;
		while (ptr->arg[i][j])
		{
			if (ft_isalpha(ptr->arg[i][j]) == 1)
			{
				printf("minishell: exit: %s: numeric argument required\n",
					ptr->arg[i]);
				exit(255);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_exit(t_bash *ptr)
{
	int	a;
	int	size_c;

	a = -404;
	size_c = 0;
	if (ptr->arg)
		size_c = ft_count_2d(ptr->arg);
	if (!ptr)
		return ;
	if (size_c == 0)
		exit(t_e.exit_status);
	if (_ft_exit_v(ptr, size_c) == 1)
		return ;
	_ft_exit_check_arg(ptr);
	if (ptr->arg[0])
		a = ft_atoi(ptr->arg[0]);
	else
		exit(t_e.exit_status);
	if (a != -404)
		exit(a);
}

void	ft_delete_node_env(t_list_env **head, char *key)
{
	t_list_env	*temp;
	t_list_env	*current;

	current = *head;
	if (ft_strcmp((*head)->key, key) == 0)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp->content);
		free(temp->key);
		free(temp->value);
		free(temp);
	}
	else
		ft_second_delete_func_part(head, key);
}
