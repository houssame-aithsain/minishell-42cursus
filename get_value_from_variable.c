/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value_from_variable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:56:47 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/05/26 00:23:01 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_rewrite(char **holder)
{
	int i;

	i = 0;
	while(*holder && (*holder)[i])
	{
		if ((*holder)[i] == 10)
			(*holder)[i] = '$';
		i++;
	}
}

char *ft_get_value(char *arg, char **key, char quote_type, t_list_export *exp_list, int len)
{
	int k;
	int i;

	i = 0;
	// printf("ft_get_value*********>%s\n", arg);
	while (arg && arg[i] && arg[i] != quote_type)
	{
		k = -1;
		// printf("ALX!\n");
		while (++k < len)
		{
			// printf("ALX key! %s\n",key[k]);
			if (key && key[k])
			{
				// printf("keyyyyy===>{%s}\n",key[k]);
				if (!ft_strncmp(arg + i, key[k], ft_strlen(key[k])))
				{
					// printf("chack key===={%s}\n",key[k]);
					if (get_val_for_a_specific_key(exp_list, key[k]))
						return key[k];
					else
						return NULL;
				}
			}
		}
		i++;
	}
	// printf("ft_get_value not valid[%c]\n",arg[i]);'
	// printf("out!\n");
	return NULL;
}
int check_if_var(char *str, char quote_type)
{
	int i;

	i = 0;
	// printf("chack str===={%s}\n",str);
	if (quote_type == 39)
		return 0;
	if (str[i] == quote_type && quote_type)
		i++;
	if (str[i] && (str[i] != quote_type || !quote_type))
	{
		while (str && str[i] && str[i] != quote_type)
		{
			if (str[i] == '$')
			{
				if (str[i - 1] == '$')
					return 0;
				if ((ft_isdigit(str[i + 1]) || ft_isalpha(str[i + 1])))
					return 1;
				else
					return 0;
			}
			i++;
		}
	}
	return 0;
}

char *ft_replace_var_by_value(char **arg, t_ex *ex, t_list_export *exp_list, int l, char *rt_value, int len, int i)
{
	// printf("str======================> %s\n",*arg);
	char *value;
	char *s_key;
	int quote_numb;
	int str_lent;
	char quote_type;
	int j;
	
	j = 0;
	quote_numb = 0;
	quote_type = 0;
	str_lent = 0;
	if (!l)
		rt_value = malloc(sizeof(char) * ft_strlen(*arg) + 1000000);
	while (arg && (*arg)[i])
	{
		quote_type = quote_typ(*arg + i, '"', 39, 1);
		// printf("quote_type==={%c}!\n",quote_type);
		if (ft_get_value(*arg + i + 1, ex->key, quote_type, exp_list, ex->len) && check_if_var(*arg + i, quote_type))
		{
			// printf("worked!\n");
			j = 0;
			s_key = ft_get_value(*arg + i + 1, ex->key, quote_type, exp_list, ex->len);
			if (checker_export(s_key))
			{
				value = get_val_for_a_specific_key(exp_list, s_key);
				value = ft_strtrim(value, "\1");
			}
			while ((*arg)[i] && (*arg)[i] != '$')
				rt_value[l++] = (*arg)[i++];
			while (value && value[j])
			{
				// 8 for '
				// 9 for "
				if (value[j] == 39)
					rt_value[l++] = 8;
				else if (value[j] == '"')
					rt_value[l++] = 9;
				else
					rt_value[l++] = value[j];
				j++;
			}
			if ((*arg)[i] == '$')
				i++;
			while (arg && (*arg)[i] && (*arg)[i] != 39 && (*arg)[i] != ' ' && (*arg)[i] != '"' && (*arg)[i] != '$' && (*arg)[i] != '*' && (*arg)[i] != '_' && (*arg)[i] != '@' && (ft_isdigit((*arg)[i]) || ft_isalpha((*arg)[i])))
				i++;
			if ((*arg)[i])
				ft_replace_var_by_value(arg, ex, exp_list, l, rt_value, len, i);
		}
		else
		{
			if ((*arg)[i] == '$')
			{
				rt_value[l++] = 10;
				i++;
			}
			while((*arg)[i] && (*arg)[i] != '$')
				rt_value[l++] = (*arg)[i++];
		}
	}
	// rt_value[l] = 0;
	// printf("after expande===={%s}\n",rt_value);
	return rt_value;
}

char *ft_get_arg(char *str)
{
	int i;
	char *value;

	i = 0;
	value = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str && str[i] && str[i] != ' ' && str[i] != '"' && str[i] != 39 && str[i] != '$' && str[i] != '*' && str[i] != '@' &&(!ft_isdigit(str[i]) || !ft_isalpha(str[i]) || str[i] == '_'))
	{
		value[i] = str[i];
		i++;
	}
	if (!i)
	{
		free(value);
		return (NULL);
	}
	value[i] = 0;
	return value;
}

int get_key(char *arg, char **str)
{
	int i;

	i = 0;
	// printf("arg ----------->%s<-----------\n", arg);
	while (arg && arg[i])
	{
		if (arg[i] == '$')
		{
			*str = ft_get_arg(arg + i + 1);
			{
				// printf("check befooooooore ex->key----------->%s<-----------\n", *str);
				// printf("check befooooooore (i)----------->%d<-----------\n", i);
				return i;
			}
		}
		i++;
	}
	str = NULL;
	return i;
}

t_ex *get_value_from_variable(t_list_export *exp_list, char **holder)
{
	char *rt_value;
	size_t cmd_lent;
	t_ex *ex;
	int j;
	int i;
	int mlc;
	char *tmp_value;

	i = 0;
	mlc = 0;
	cmd_lent = 0;
	ex = malloc(sizeof(t_ex));
	ex->len = 0;
	while ((*holder)[i])
	{
		if ((*holder)[i] == '$')
			mlc++;
		i++;
	}
	// printf("MLC %d\n", mlc);
	ex->key = malloc(sizeof(char *) * (mlc + 1));
	while (ex->len < mlc)
	{
		get_key(*holder + cmd_lent, &ex->key[ex->len]);
		if (ex->key[ex->len])
			cmd_lent += ft_strlen(ex->key[ex->len]) + 1;
	// printf("check ex->key----------->%s<-----------\n", ex->key[ex->len]);
		ex->len++;
	}
	ex->key[ex->len] = NULL;
	i = 0;
	*holder = ft_replace_var_by_value(holder, ex, exp_list, 0, rt_value, j, 0);
	ft_rewrite(holder);
	// printf("afterex=====>%s<======\n",*holder);
	return ex;
}