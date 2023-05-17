/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readl_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:33:53 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/05/17 19:53:19 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_if_valide(char *ncoom, int i)
{
	char quote_type;
	int quote_numb;

	quote_numb = 0;
	quote_type = 0;
	while (ncoom && ncoom[i])
	{
		if (ncoom[i] == '"')
		{
			quote_type = '"';
			quote_numb++;
			break;
		}
		if (ncoom[i] == 39)
		{
			quote_type = 39;
			quote_numb++;
			break;
		}
		i++;
	}
	if (!quote_type)
		return (0);
	i = 0;
	while (ncoom && ncoom[i])
	{
		if (ncoom[i] == quote_type)
			quote_numb++;
		i++;
	}
	if (!(quote_numb % 2) && quote_numb)
		return 0;
	return 1;
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
	quote_type = 0;
	while (ncoom && ncoom[i])
	{
		if (ncoom[i] == '"')
		{
			quote_type = '"';
			break;
		}
		if (ncoom[i] == 39)
		{
			quote_type = 39;
			break;
		}
		if (ncoom[i] == '>' || ncoom[i] == '<')
			break;
		i++;
	}
	i = 0;
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
				while (ncoom[i] && ncoom[i] == ' ')
					i++;
				if ((ncoom[i] == '>' || ncoom[i] == '<') && quote_numb % 2 && quote_numb)
				{
					while(ncoom[i])
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
		{
			// if (check_if_valide(ncoom, i))
			// 	return 0;
			// else
			return ">>\0";
		}
		else if (!ft_memcmp(ncoom + i, "<<", 2))
		{
			// if (check_if_valide(ncoom, i))
			// 	return 0;
			// else
			return "<<\0";
		}
		else if (ncoom[i] == '>')
		{
			// if (check_if_valide(ncoom, i))
			// 	return 0;
			// else
			return ">\0";
		}
		else if (ncoom[i] == '<')
		{
			// if (check_if_valide(ncoom, i))
			// 	return 0;
			// else
			return "<\0";
		}
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
			if (tmp[i] == '>' || tmp[i] == '<')
				i++;
			while (tmp[i] == ' ')
				i++;
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
		i++;
	}
}

void ft_copy(char *dst, char qoute_type, int *v, int *j, char *command)
{
	int quote_numb;

	quote_numb = 1;
	(*v)++;
	while (dst[*v])
	{
		if (dst[*v] == '"' || dst[*v] == 39)
		{
			if (dst[*v] == qoute_type)
				quote_numb++;
			if (dst[*v] != qoute_type && !(quote_numb % 2))
				break;
		}
		if (dst[*v] != qoute_type)
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
	int v;
	int j;
	int i;
	int arg_count;
	int s_qoute;
	int d_qoute;
	char *command;
	char **arg;
	char *file;
	char qoute_type;

	i = 0;
	v = 0;
	s_qoute = 0;
	d_qoute = 0;
	tmp = *ptr;
	head = *ptr;
	if (!ptr || !*ptr)
		return;
	while ((*ptr)->command && (*ptr)->command[i])
	{
		if ((*ptr)->command[i] == 39)
			s_qoute++;
		if ((*ptr)->command[i] == '"')
			d_qoute++;
		i++;
	}
	arg = tmp->arg;
	while (tmp)
	{
		i = 0;
		j = 0;
		v = 0;
		command = malloc(sizeof(char) * ft_strlen(tmp->command) + 100);
		arg = malloc(sizeof(char *) * arg_lent(tmp->arg) + 1);
		while (tmp->command[v])
		{
			if (tmp->command[v] == 39)
			{
				qoute_type = 39;
				ft_copy(tmp->command, qoute_type, &v, &j, command);
			}
			else if (tmp->command[v] == '"')
			{
				qoute_type = '"';
				ft_copy(tmp->command, qoute_type, &v, &j, command);
			}
			else
				command[j++] = tmp->command[v++];
		}
		command[j] = 0;
		while (tmp->arg[i])
		{
			j = 0;
			arg_count = 0;
			arg[i] = malloc(sizeof(char) * ft_strlen(tmp->arg[i]));
			qoutes_counter(tmp->arg[i], &s_qoute, &d_qoute);
			while (tmp->arg[i] && tmp->arg[i][j])
			{
				if (tmp->arg[i][j] == 39)
				{
					qoute_type = 39;
					ft_copy(tmp->arg[i], qoute_type, &j, &arg_count, arg[i]);
				}
				else if (tmp->arg[i][j] == '"')
				{
					qoute_type = '"';
					ft_copy(tmp->arg[i], qoute_type, &j, &arg_count, arg[i]);
				}
				else
					arg[i][arg_count++] = tmp->arg[i][j++];
			}
			arg[i][arg_count] = 0;
			i++;
		}
		arg[i] = NULL;
		tmp->command = command;
		tmp->arg = arg;
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

char *leave_it_for_me(char *str)
{
	char qoute_type;
	int i;
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
					str[i] = '~';
				i++;
			}
		}
		// printf("holder====={%s\n}",holder);
		else if (str[i] == 39)
		{
			i++;
			while (str[i] && str[i] != 39)
			{
				if (str[i] == ' ')
					str[i] = '~';
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
	char *tmp;
	char *holder;
	int error;
	int qoute_numb;
	int dqoute_numb;
	int o_count;
	int i;
	int j;

	i = 0;
	error = 0;
	holder = malloc(sizeof(char) * ft_strlen(ncoom));
	*ptr = NULL;
	while (ncoom && ncoom[i])
	{
		j = 0;
		qoute_numb = 0;
		dqoute_numb = 0;
		while (ncoom[i])
		{
			if (ncoom[i] == '"')
			{
				holder[j++] = ncoom[i++];
				while (ncoom[i] && ncoom[i] != '"')
					holder[j++] = ncoom[i++];
			}
			// printf("holder====={%s\n}",holder);
			else if (ncoom[i] == 39)
			{
				holder[j++] = ncoom[i++];
				while (ncoom[i] && ncoom[i] != 39)
					holder[j++] = ncoom[i++];
			}
			if (ncoom[i])
			{
				if (ncoom[i] == '|')
				{
					// check_for_error(ncoom , &error, 0, i + 1, 0, 0);
					break;
				}
				else
					holder[j++] = ncoom[i++];
			}
		}
		if (ncoom[i] == '|')
		{
			holder[j++] = '|';
			i++;
		}
		// printf("==%s==\n", holder);
		holder[j] = 0;
		holder = leave_it_for_me(holder);
		// printf("before[%s]\n", holder);
		check_for_error(holder, &error);
		nodepush(ptr, holder, 1);
		(*ptr)->error = error;
	}
	qoutes_remover(ptr);
}

void readl_to_parse()
{
	t_bash *ptr;
	t_var *var;
	int i;
	char *line;
	char *ncoom;

	ncoom = NULL;
	var = malloc(sizeof(t_var));
	ptr = malloc(sizeof(t_bash));
	while (TRUE)
	{
		i = 0;
		line = NULL;
		line = readline("minishell$> ");
		add_history(line);
		get_the_right_forma(line, &ptr);

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
			while(ptr->redirection[h])
				printf("redirection=[%s]\n", ptr->redirection[h++]);
			while(ptr->file[f])
				printf("file=[%s]\n", ptr->file[f++]);
			printf("operator=[%c]\n", ptr->operator);
			printf("error=[%d]\n", ptr->error);
			ptr = ptr->link;
		}
	}
}