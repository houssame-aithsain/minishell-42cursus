/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_s_node_args_ready.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 00:51:45 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/14 23:14:54 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_and_build_linked_list(t_format *var, t_bash **ptr, t_ex *expn)
{
	while (expn->holder && expn->holder[var->i])
	{
		var->container = malloc(sizeof(char) * ft_strlen(expn->holder) + 1);
		var->j = 0;
		var->q_cnt = 0;
		var->dq_cnt = 0;
		extract_q_segments(var, expn);
		if (expn->holder[var->i] == '|')
		{
			var->container[var->j++] = '|';
			var->i++;
		}
		var->container[var->j] = 0;
		var->container = spaces_trim(var->container);
		list_builder(ptr, var->container, 1);
		(*ptr)->error = 0;
		if (var->error)
			(*ptr)->error = var->error;
		else if (expn->error)
			(*ptr)->error = expn->error;
		heredoc_cmd_finder(ptr);
		free(var->container);
	}
}

void	list_parse(char *str, t_bash **ptr, t_list_env **env_list,
		t_list_export **exp_list)
{
	t_ex		*expn;
	t_format	var;

	(void)env_list;
	var.i = 0;
	var.error = 0;
	var.container = NULL;
	check_str_errors(str, &var.error);
	expn = get_expand_vars(*exp_list, str);
	parse_and_build_linked_list(&var, ptr, expn);
	quote_sanitizer(ptr, expn);
	quotes_rewriter(ptr);
	var.i = 0;
	while (expn->key && var.i < expn->len)
		free(expn->key[var.i++]);
	free(expn->key);
	free(expn->holder);
	free(expn);
}
