/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readl_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:33:53 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/15 18:33:29 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_j_env(char **env)
{
	int		i;
	char	**momo;

	i = 0;
	momo = ft_calloc(sizeof(char *), (ft_count_2d(env) + 1));
	while (env[i])
	{
		momo[i] = ft_strdup(env[i]);
		i++;
	}
	return (momo);
}

void	_rl_routine(t_readl_main	*s)
{
	add_history(s->line);
	list_parse(s->line, &(s->ptr), &(s->env_ls), &(s->exp_ls));
	free(s->line);
	if (s->ptr && !print_error(s->ptr))
		n_pipe(s->ptr, &(s->env_ls), &(s->exp_ls));
	_ft_free_main_t(s);
}

void	readl_to_parse(char **env_v)
{
	t_readl_main	s;
	t_list_env		*as;
	char			**env;

	env = ft_j_env(env_v);
	_ft_main_vars_init_t(env, &s, &as);
	t_e.r = 1;
	while (TRUE)
	{
		_ft_signal_init_t(&s);
		_ft_update_exit_status(&(s.exp_ls), t_e.exit_status);
		s.line = readline("minishell$> ");
		if (!s.line)
		{
			if (t_e.rl_catch_signals == 1)
			{
				t_e.exit_status = 1;
				continue ;
			}
			exit(t_e.exit_status);
		}
		_rl_routine(&s);
	}
	ft_free_args(env);
}
