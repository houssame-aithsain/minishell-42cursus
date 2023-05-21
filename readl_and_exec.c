/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readl_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:33:53 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/05/21 22:53:34 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//gothmane functions

// char    *get_val_for_a_specific_key(t_list_export *exp, char *key)
// {
//     t_list_export *e;

//     e = exp;
//     while (e)
//     {
//         if (ft_strcmp(e->key, key) == 0)
//             return (e->value);
//         e = e->next;
//     }
//     return (NULL);
// }

// int    checker_export(char *str)
// {
//    int    i;

//    i = 0;
//    while (str[i])
//    {
//         if (i == 0 && (!ft_isalpha(str[i]) && str[i] != '_'))
//             return (0);
//         else if ((ft_isdigit(str[i]) || ft_isalpha(str[i]) || str[i] == '_') 
//             || (str[i] == '+' && str[i + 1] == '='))
//             i++;
//         else
//             return (0);
//         if (str[i] == '=')
//             break;
//    }
//    return (1);
// }

//END gothmane functions

char quote_typ(char *ncoom, char f_type, char s_type)
{
	char quote_type;
	int i;

	i = 0;
	quote_type = 0;
	while (ncoom && ncoom[i])
	{
		if (ncoom[i] == f_type)
		{
			quote_type = f_type;
			break;
		}
		if (ncoom[i] == s_type)
		{
			quote_type = s_type;
			break;
		}
		if (ncoom[i] == '>' || ncoom[i] == '<')
			break;
		i++;
	}
	return quote_type;
}

char *if_operatore(char *ncoom)
{
	int i;
	char quote_type;
	int quote_numb;
	int skipe;

	quote_numb = 0;
	i = 0;
	skipe = 0;
	quote_type = quote_typ(ncoom, '"', 39);
	while (ncoom && ncoom[i] && quote_type)
	{
		if (ncoom[i] == quote_type)
		{
			quote_numb++;
			i++;
			while (ncoom[i])
			{
				while (ncoom[i] && ncoom[i] == quote_type)
				{
					quote_numb++;
					i++;
				}
				if (!ncoom[i])
					break;
				while (ncoom[i] && ncoom[i] == ' ')
					i++;
				if ((ncoom[i] == '>' || ncoom[i] == '<') && quote_numb % 2 && quote_numb)
				{
					while (ncoom[i])
					{
						if (ncoom[i] == quote_type)
							quote_numb++;
						if (ncoom[i] == '>' || ncoom[i] == '<')
						{
							if (!(quote_numb % 2) && quote_numb)
								skipe = 1;
						}
						i++;
					}
					if (!skipe)
						return 0;
					else
						break;
				}
				else if ((ncoom[i] == '>' || ncoom[i] == '<') && !(quote_numb % 2) && quote_numb)
				{
					skipe = 8;
				}
				i++;
			}
			if (skipe == 8)
				break;
		}
		if (!ncoom[i])
			break;
		i++;
	}
	i = 0;
	while (ncoom && ncoom[i])
	{
		if (!ft_memcmp(ncoom + i, ">>", 2))
			return ">>\0";
		else if (!ft_memcmp(ncoom + i, "<<", 2))
			return "<<\0";
		else if (ncoom[i] == '>')
			return ">\0";
		else if (ncoom[i] == '<')
			return "<\0";
		i++;
	}
	return 0;
}

void qoutes_counter(char *arg, int *s_qoute, int *d_qoute)
{
	int i;

	i = 0;
	*s_qoute = 0;
	*d_qoute = 0;
	while (arg && arg[i])
	{
		if (arg[i] == 39)
			*s_qoute += 1;
		if (arg[i] == '"')
			*d_qoute += 1;
		i++;
	}
}

void check_for_error(char *tmp, int *error)
{
	int i;
	char quote_type;

	i = 0;
	while (tmp && tmp[i])
	{
		if (tmp[i] == '\\')
			*error = BACK_SLASH;
		if (tmp[i] == ';')
			*error = SEMICOLON;
		if (tmp[i] == '"')
		{
			i++;
			while (tmp[i] && tmp[i] != '"')
				i++;
			if (tmp[i] != '"')
				*error = D_QUOTE;
		}
		if (tmp[i] == 39)
		{
			i++;
			while (tmp[i] && tmp[i] != 39)
				i++;
			if (tmp[i] != 39)
				*error = S_QUOTE;
		}
		if (!tmp[i])
			break;
		i++;
	}
	i = 0;
	while (tmp && tmp[i])
	{
		if (tmp[i] == '>' || tmp[i] == '<')
		{
			i++;
			quote_type = quote_typ(tmp, '>', '<');
			if (tmp[i] == quote_type)
				i++;
			while (tmp[i] == ' ')
				i++;
			if (tmp[i] == '|')
				*error = PIPE;
			if (tmp[i] == '>' || tmp[i] == '<')
				*error = RD_ERROR;
			if (!tmp[i])
				*error = S_RD_ERROR;
			if (tmp[i] == '"' || tmp[i] == 39)
			{
				i++;
				if (tmp[i] == '"' || tmp[i] == 39)
				{
					i++;
					if (!tmp[i] || tmp[i] == ' ')
						*error = NSFOD;
				}
			}
		}
		if (tmp[i] == '|')
		{
			i++;
			while (tmp[i] == ' ')
				i++;
			if (!tmp[i] || tmp[i] == '|')
				*error = PIPE;
		}
		i++;
	}
}

void ft_copy(char *dst, t_rquotes *var, int flag)
{
	int quote_numb;
	int *v;
	int *j;
	char *command;
	if (!flag)
	{
		v = &var->v;
		j = &var->j;
		command = var->command;
	}
	else
	{
		v = &var->j;
		j = &var->arg_count;
		command = var->arg[var->i];
	}
	quote_numb = 1;
	(*v)++;
	while (dst[*v])
	{
		if (dst[*v] == '"' || dst[*v] == 39)
		{
			if (dst[*v] == var->qoute_type)
				quote_numb++;
			if (dst[*v] != var->qoute_type && !(quote_numb % 2))
				break;
		}
		if (dst[*v] != var->qoute_type)
			command[(*j)++] = dst[*v];
		(*v)++;
	}
	command[*j] = 0;
}

int arg_lent(char **arg)
{
	int i;

	i = 0;
	while (arg && arg[i])
		i++;
	return i;
}

void qoutes_remover(t_bash **ptr)
{
	t_bash *tmp;
	t_bash *head;
	t_rquotes var;

	var.i = 0;
	var.v = 0;
	var.s_qoute = 0;
	var.d_qoute = 0;
	tmp = *ptr;
	head = *ptr;
	if (!ptr || !*ptr)
		return;
	while ((*ptr)->command && (*ptr)->command[var.i])
	{
		if ((*ptr)->command[var.i] == 39)
			var.s_qoute++;
		if ((*ptr)->command[var.i] == '"')
			var.d_qoute++;
		var.i++;
	}
	var.arg = tmp->arg;
	while (tmp)
	{
		var.i = 0;
		var.j = 0;
		var.v = 0;
		var.command = malloc(sizeof(char) * ft_strlen(tmp->command) + 1);
		var.arg = malloc(sizeof(char *) * (arg_lent(tmp->arg) + 1));
		while (tmp->command[var.v])
		{
			if (tmp->command[var.v] == 39)
			{
				var.qoute_type = 39;
				ft_copy(tmp->command, &var, 0);
			}
			else if (tmp->command[var.v] == '"')
			{
				var.qoute_type = '"';
				ft_copy(tmp->command, &var, 0);
			}
			else
				var.command[var.j++] = tmp->command[var.v++];
		}
		var.command[var.j] = 0;
		while (tmp->arg[var.i])
		{
			var.j = 0;
			var.arg_count = 0;
			var.arg[var.i] = malloc(sizeof(char) * ft_strlen(tmp->arg[var.i]) + 1);
			qoutes_counter(tmp->arg[var.i], &var.s_qoute, &var.d_qoute);
			while (tmp->arg[var.i] && tmp->arg[var.i][var.j])
			{
				if (tmp->arg[var.i][var.j] == 39)
				{
					var.qoute_type = 39;
					ft_copy(tmp->arg[var.i], &var, 1);
				}
				else if (tmp->arg[var.i][var.j] == '"')
				{
					var.qoute_type = '"';
					ft_copy(tmp->arg[var.i], &var, 1);
				}
				else
					var.arg[var.i][var.arg_count++] = tmp->arg[var.i][var.j++];
			}
			var.arg[var.i][var.arg_count] = 0;
			var.i++;
		}
		var.arg[var.i] = NULL;
		var.i = 0;
		int x = (arg_lent(tmp->arg) + 1);
		while(var.i < x)
			free(tmp->arg[var.i++]);
		free(tmp->arg);
		free(tmp->command);
		tmp->command = var.command;
		tmp->arg = var.arg;
		tmp = tmp->link;
	}
	ptr = &head;
}

int pipe_checker(char *ncoom)
{
	int i;

	i = 0;
	while (ncoom[i] && ncoom[i] == ' ')
		i++;
	if (ncoom[i++] == '|')
		return (1);
	return 0;
}

char *replace_spaces_in_quotes(char *str)
{
	int i;
	char qoute_type;
	int single_qoute;
	int doble_qoute;

	single_qoute = 0;
	doble_qoute = 0;
	i = 0;
	while (str && str[i])
	{

		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
			{
				if (str[i] == ' ')
					str[i] = 11;
				i++;
			}
		}
		else if (str[i] == 39)
		{
			i++;
			while (str[i] && str[i] != 39)
			{
				if (str[i] == ' ')
					str[i] = 11;
				i++;
			}
		}
		if (!str[i])
			break;
		i++;
	}
	return str;
}

void get_the_right_forma(char *ncoom, t_bash **ptr)
{
	t_format var;

	var.i = 0;
	var.error = 0;
	*ptr = NULL;
	check_for_error(ncoom, &var.error);
	var.holder = malloc(sizeof(char) * ft_strlen(ncoom) + 1);
	while (ncoom && ncoom[var.i])
	{
		var.j = 0;
		var.qoute_numb = 0;
		var.dqoute_numb = 0;
		while (ncoom[var.i])
		{
			if (ncoom[var.i] == '"')
			{
				var.holder[var.j++] = ncoom[var.i++];
				while (ncoom[var.i] && ncoom[var.i] != '"')
					var.holder[var.j++] = ncoom[var.i++];
				var.holder[var.j++] = ncoom[var.i++];
			}
			else if (ncoom[var.i] == 39)
			{
				var.holder[var.j++] = ncoom[var.i++];
				while (ncoom[var.i] && ncoom[var.i] != 39)
					var.holder[var.j++] = ncoom[var.i++];
				var.holder[var.j++] = ncoom[var.i++];
			}
			if (ncoom[var.i])
			{
				if (ncoom[var.i] == '|')
					break;
				else
					var.holder[var.j++] = ncoom[var.i++];
			}
		}
		if (ncoom[var.i] == '|')
		{
			var.holder[var.j++] = '|';
			var.i++;
		}
		var.holder[var.j] = 0;
		var.holder = replace_spaces_in_quotes(var.holder);
		// printf("before[%s]\n", var.holder);
		nodepush(ptr, var.holder, 1);
		(*ptr)->error = var.error;
	}
	// printf("var.holder=========={%p}\n", var.holder);
	free(var.holder);
	qoutes_remover(ptr);
}

void readl_to_parse(char **env)
{
	t_bash *ptr;
	int i;
	int get;
	char *line;
	t_list_export *exp_list;
	t_list_env	*env_list;
	
	get = 0;
	ptr = malloc(sizeof(t_bash));
	env_list = put_env_to_ls(env);
	exp_list = ft_create_export_lst(env);
	while (TRUE)
	{
		i = 0;
		line = NULL;
		line = readline("minishell$> ");
		add_history(line);
		get_the_right_forma(line, &ptr);
		free(line);
		if (ptr)
		{
			if (!ft_strcmp("export", ptr->command))
			{
				ft_export(&exp_list, ptr->arg, &env_list);
				if (!ptr->arg[0])
					ft_print_lst(exp_list);
			}
			get_value_from_variable(exp_list, &ptr);
		}
		//=========================>ptr is the head bitch!<===========================//

		// printf("(%s)\n",ncoom);
		// free(line);
		// free(ncoom);
		int x = 0;
		int h = 0;
		int f = 0;
		while (ptr)
		{

			
			x = 0;
			h = 0;
			f = 0;
			printf("-------------------\n");
			printf("command=[%s]\n", ptr->command);
			while (ptr->arg[x])
				printf("arg=[%s]\n", ptr->arg[x++]);
			while (ptr->redirection && ptr->redirection[h])
				printf("redirection=[%s]\n", ptr->redirection[h++]);
			while (ptr->file && ptr->file[f])
				printf("file=[%s]\n", ptr->file[f++]);
			printf("operator=[%c]\n", ptr->operator);
			printf("error=[%d]\n", ptr->error);
			// free
			// x = 0;
			// while(x < ptr->red)
			// {
			// 	free(ptr->file[x]);
			// 	free(ptr->redirection[x]);
			// 	x++;
			// }
			// free(ptr->file);
			// free(ptr->redirection);
			// x = 0;
			// printf("agrs_malloc=={%d}\n", ptr->args_malloc);
			// while(ptr->arg[x])
			// 	free(ptr->arg[x++]);
			// 	free(ptr->arg[x++]);
			// free(ptr->arg);
			// free(ptr->command);
			// free(ptr);

			
			// end free
			ptr = ptr->link;
		}
	}
}


