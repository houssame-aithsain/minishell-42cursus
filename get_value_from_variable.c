/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value_from_variable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:56:47 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/05/21 23:06:09 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_replace_var_by_value(char *arg, char *value)
{
	int stope;
	int l;
	int j;
	int i;
	char *rt_value;

	i = 0;
	j = 0;
	l = 0;
	stope = 1;
	rt_value = malloc(sizeof(char) * (ft_strlen(arg) + ft_strlen(value)) + 100000);
	while (arg && arg[i])
	{
		if (arg[i] == '$' && stope)
		{
			stope = 0;
			j = 0;
			while (value[j])
				rt_value[l++] = value[j++];
			i++;
			while (arg && arg[i] && arg[i] != ' ' && arg[i] != '$' && arg[i] != '*' && arg[i] != '_' && (ft_isdigit(arg[i]) && ft_isalpha(arg[i])))
				i++;
		}
		else
			rt_value[l++] = arg[i];
		if (!arg[i])
			break;
		i++;
	}
	free(arg);
	rt_value[l] = 0;
	return rt_value;
}

char *ft_get_str(char *str)
{
	int i;
	char *value;

	i = 0;
	value = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str && str[i] && str[i] != ' ' && str[i] != '$' && str[i] != '*' && (!ft_isdigit(str[i]) || !ft_isalpha(str[i]) || str[i] == '_'))
	{
		value[i] = str[i];
		i++;
	}
	value[i] = 0;
	return value;
}

char *get_key(char *arg)
{
	int i;
	char *str;

	i = 0;
	while (arg && arg[i])
	{
		if (arg[i] == '$')
		{
			str = ft_get_str(arg + i + 1);
			return str;
		}
		i++;
	}
	str = NULL;
	return str;
}

void get_value_from_variable(t_list_export *exp_list, t_bash **ptr)
{
	size_t cmd_lent;
	int j;
	int i;
	int mlc;
	char **key_cmd;
	char **key_arg;
	char *tmp_value;
	t_bash *tmp;
	t_bash *head;

	tmp = *ptr;
	head = tmp;
	while (tmp)
	{
		i = 0;
		j = 0;
		mlc = 0;
		cmd_lent = 0;
		while (tmp->command[i])
		{
			if (tmp->command[i] == '$')
				mlc++;
			i++;
		}
		key_cmd = malloc(sizeof(char *) * (mlc + 1));
		i = -1;
		while (++i < mlc)
		{
			key_cmd[j] = get_key(tmp->command + cmd_lent);
			if (key_cmd[j])
				cmd_lent += ft_strlen(key_cmd[j]);
			j++;
		}
		key_cmd[j] = NULL;
		i = 0;
		while (i < j)
		{
			if (key_cmd[i])
			{
				if (checker_export(key_cmd[i]))
				{
					if (key_cmd[i])
					{
						tmp_value = get_val_for_a_specific_key(exp_list, key_cmd[i]);
						tmp_value = ft_strtrim(tmp_value, "\1");
						if (tmp_value)
							tmp->command = ft_replace_var_by_value(tmp->command, tmp_value);
					}
				}
			}
			i++;
		}
		mlc = 0;
		while (tmp->arg[mlc])
		{
			i = -1;
			j = 0;
			cmd_lent = 0;
			while (tmp->arg[mlc][++i])
			{
				if (tmp->arg[mlc][i] == '$')
					j++;
			}
			if (!j)
				return;
			key_arg = malloc(sizeof(char *) * (j + 1));
			i = 0;
			while (i < j)
			{
				key_arg[i] = get_key(tmp->arg[mlc] + cmd_lent);
				if (key_arg[i])
					cmd_lent += ft_strlen(key_arg[i]);
				i++;
			}
			key_arg[i] = NULL;
			i = -1;
			while (++i < j)
			{
				if (key_arg[i])
				{
					if (checker_export(key_arg[i]))
					{
						if (key_arg[i])
						{
							tmp_value = get_val_for_a_specific_key(exp_list, key_arg[i]);
							tmp_value = ft_strtrim(tmp_value, "\1");
							if (tmp_value)
								tmp->arg[mlc] = ft_replace_var_by_value(tmp->arg[mlc], tmp_value);
						}
					}
				}
			}
			mlc++;
		}
		tmp = tmp->link;
	}
	ptr = &head;
}