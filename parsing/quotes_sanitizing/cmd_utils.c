/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 06:03:49 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/11 18:09:45 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free_q(t_bash *tmp, t_rquotes *var)
{
	int	i;

	i = 0;
	while (tmp->file[i])
		free(tmp->file[i++]);
	free(tmp->file);
	i = 0;
	while (tmp->arg[i])
		free(tmp->arg[i++]);
	free(tmp->arg);
	free(tmp->command);
}

int	rm_cmd_empty_vars(t_bash *tmp, t_bash **ptr, t_rquotes *var, t_ex *ex)
{
	if (ex->key[var->k_c])
	{
		if (!ft_strncmp(tmp->command + var->cmd_c,
				ex->key[var->k_c], ft_strlen(ex->key[var->k_c])))
		{
			var->l_s = ft_strlen(ex->key[var->k_c]);
			var->k_c = 0;
			while (var->k_c < var->l_s)
			{
				var->k_c++;
				var->cmd_c++;
			}
			return (1);
		}
	}
	return (0);
}

void	_q_vars_reset_(t_rquotes *var)
{
	var->count = 0;
	var->cmd_c = 0;
	var->s_qoute = 0;
	var->d_qoute = 0;
}

void	_s_q_c(t_bash **ptr, t_bash *tmp, t_rquotes *var)
{
	while ((*ptr)->command && (*ptr)->command[var->count])
	{
		if ((*ptr)->command[var->count] == 39
			|| (*ptr)->command[var->count] == '"')
			var->s_qoute++;
		var->count++;
	}
	var->arg = tmp->arg;
}

int	if_valide_c(t_bash *tmp, t_rquotes *var, t_ex *ex)
{
	if (tmp->command[var->cmd_c] && tmp->command[var->cmd_c] == '$'
		&& tmp->command[var->cmd_c] && tmp->command[var->cmd_c] != ' '
		&& tmp->command[var->cmd_c + 1] != '?')
		return (1);
	return (0);
}
