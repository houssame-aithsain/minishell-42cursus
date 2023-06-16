/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_four.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:58:34 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_minus_n_after(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_check_minus_n_(str[i]) == 1)
		{
			printf("%s", str[i]);
			if (str[i + 1])
				printf(" ");
		}
		i++;
	}
}

void	ft_printing_echo_content(char **str, int *i, int c)
{
	printf("%s", str[*i]);
	if (str[*i + 1])
	{
		printf(" ");
		if (c == 1)
			ft_print_minus_n_after(&str[*i]);
	}
	(*i)++;
}

void	ft_echo(char **str)
{
	int	i;
	int	c;
	int	k;

	c = 0;
	i = 0;
	k = 0;
	while (str[i])
	{
		k = ft_check_minus_n_(str[i]);
		if (i == 0 && k == 1)
		{
			c = 1;
			i++;
		}
		else if (i > 0 && k == 1 && c == 1)
			i++;
		else if (i != 0 || k == 0)
			ft_printing_echo_content(str, &i, c);
		else
			i++;
	}
	if (c == 0)
		printf("\n");
	ft_free_args(str);
}

int	ft_find_key__v2(t_list_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "HOME") == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

char	*ft_getval_env(char *key, t_list_env *env_ls)
{
	t_list_env	*env;

	env = env_ls;
	while (env)
	{
		if (ft_strcmp(key, env->key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
