/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:05:25 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	ft_isalpha_check(char c)
{
	if (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (0);
	return (1);
}

int	ft_export_arg_checker(char *arg)
{
	int	is_valid;

	is_valid = 1;
	if (arg[0] && ft_isalpha_check(arg[0]) == 0)
		is_valid = 0;
	return (is_valid);
}

int	check_if_theres_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=' || (arg[i] == '+' && arg[i + 1] == '='))
			return (0);
		i++;
	}
	return (1);
}

void	ft_print_double_arr(char **var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		printf("[%s]\n", var[i]);
		i++;
	}
}
