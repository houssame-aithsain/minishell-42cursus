/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:00:49 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/15 17:49:07 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_ft_shell_lvl(t_readl_main *s)
{
	while ((*s).env_ls)
	{
		if (ft_strcmp("SHLVL", (*s).env_ls->key) == 0)
		{
			free((*s).env_ls->value);
			(*s).env_ls->value = ft_itoa(ft_atoi((*s).env_ls->value) + 1);
			free((*s).env_ls->content);
			(*s).env_ls->content = (*s).env_ls->key;
			(*s).env_ls->content = ft_strjoin((*s).env_ls->content, "=");
			(*s).env_ls->content = ft_strjoin((*s).env_ls->content,
					(*s).env_ls->value);
		}
		(*s).env_ls = (*s).env_ls->next;
	}
}

void	_ft_main_vars_init_t(char **env, t_readl_main *s, t_list_env **as)
{
	(*s).env_ls = put_env_to_ls(env);
	(*s).exp_ls = ft_create_export_lst(env);
	*as = (*s).env_ls;
	_ft_shell_lvl(&(*s));
	(*s).fd = dup(0);
	(*s).env_ls = *as;
}

void	_ft_signal_init_t(t_readl_main *s)
{
	(*s).line = NULL;
	(*s).ptr = NULL;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	t_e.rl_catch_signals = 0;
	dup2((*s).fd, 0);
}

void	_ft_free_main_t(t_readl_main *s)
{
	while ((*s).ptr)
	{
		free((*s).ptr->command);
		(*s).i = 0;
		while ((*s).ptr->file && (*s).ptr->file[(*s).i])
			free((*s).ptr->file[(*s).i++]);
		free((*s).ptr->file);
		(*s).i = 0;
		while ((*s).ptr->redirection && (*s).ptr->redirection[(*s).i])
			free((*s).ptr->redirection[(*s).i++]);
		free((*s).ptr->redirection);
		(*s).i = 0;
		while ((*s).ptr->arg && (*s).ptr->arg[(*s).i])
			free((*s).ptr->arg[(*s).i++]);
		free((*s).ptr->arg);
		(*s).tmp = (*s).ptr->link;
		free((*s).ptr);
		(*s).ptr = (*s).tmp;
	}
}
