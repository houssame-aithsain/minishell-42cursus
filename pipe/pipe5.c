/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:22:13 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	_ft_pipe_init_vars(t_pipe_s *sp)
{
	(*sp).i = 0;
	(*sp).pid = 0;
	(*sp).fd = 0;
	(*sp).number_of_pipes = 0;
	(*sp).status = 0;
	(*sp).j = 0;
	(*sp).e = NULL;
	(*sp).tmp = NULL;
}

int	ft_count_cmds_exp(t_bash *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->link;
	}
	return (i);
}

int	ft_lstsize_env(t_list_env *lst)
{
	int			count;
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
	new_ls[i] = 0;
	return (new_ls);
}
