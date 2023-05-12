/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readl_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:33:53 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/05/12 18:54:25 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	qoutes_counter(char *arg, int *s_qoute, int *d_qoute)
{
	int i;
	
	i = 0;
	*s_qoute = 0;
	*d_qoute = 0;
	while(arg[i])
	{
		if (arg[i] == 39)
			*s_qoute += 1;
		if (arg[i] == '"')
			*d_qoute += 1;
		i++;
	}
}

void	check_for_error(int *error,int qoute_type, int s_qoute, int d_qoute)
{
	if (qoute_type == 39)
	{
		if (s_qoute % 2 && s_qoute)
			*error = 1;
	}
	if (qoute_type == '"')
	{
		if (d_qoute % 2 && d_qoute)
			*error = 2;
	}
}

void	ft_copy(char *dst, char qoute_type, int *v, int *j, char *command)
{
	(*v)++;
	while (dst[*v])
	{
		if (dst[*v] != qoute_type)
			command[(*j)++] = dst[*v];
		(*v)++;
	}
	command[*j] = 0;
	// printf("command=|%s|\n",command);
}

int	arg_lent(char **arg)
{
	int i;

	i = 0;
	while(arg && arg[i])
		i++;
	return i;
}

void	qoutes_remover(t_list **ptr)
{
	t_list	*tmp;
	t_list	*head;
	int		v;
	int		j;
	int		i;
	int		arg_count;
	int		s_qoute;
	int		d_qoute;
	char	*command;
	char	**arg;
	char	qoute_type;
	
	i = 0;
	v = 0;
	s_qoute = 0;
	d_qoute = 0;
	tmp = *ptr;
	head = *ptr;
	while((*ptr)->command && (*ptr)->command[i])
	{
		if ((*ptr)->command[i] == 39)
			s_qoute++;
		if ((*ptr)->command[i] == '"')
			d_qoute++;
		i++;
	}
	arg = tmp->arg;
	while(tmp)
	{
		i = 0;
		j = 0;
		v = 0;
		command = malloc(sizeof(char) * ft_strlen(tmp->command) + 100);
		arg = malloc(sizeof(char *) * arg_lent(tmp->arg) + 1);
		while(tmp->command[v])
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
		check_for_error(&tmp->error,qoute_type, s_qoute, d_qoute);
		while(tmp->arg[i])
		{
			j = 0;
			arg_count = 0;
			arg[i] = malloc(sizeof(char) * ft_strlen(tmp->arg[i]));
			// printf("hahwa=%s\n",tmp->arg[i]);
			qoutes_counter(tmp->arg[i], &s_qoute, &d_qoute);
			// printf("d_quote=%d\n",d_qoute);
			while(tmp->arg[i] && tmp->arg[i][j])
			{
				if (tmp->arg[i][j] == 39)
				{
					// printf("yeah!\n");
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
			// printf("d_quote=%d\n",d_qoute);
			// printf("quote_type=%c\n",qoute_type );
			check_for_error(&tmp->error,qoute_type, s_qoute, d_qoute);
			// printf("error=[%d]\n",tmp->error);
			
			i++;
		}
		arg[i] = NULL;
		tmp->command = command;
		tmp->arg = arg;
		tmp = tmp->link;
	}
	ptr = &head;
}

int	pipe_checker(char *ncoom, int i, int qoute_numb, int dqoute_numb)
{
	if (ncoom[i] && ncoom[i] == '|')
	{
		while(ncoom[i])
		{
			if ((ncoom[i] == '"' && dqoute_numb && dqoute_numb % 2) || (ncoom[i] == 39 && qoute_numb && qoute_numb % 2))
			{
				return (1);
			}
			i++;
		}
		return (0);
	}
	return 1;
}

char	*leave_it_for_me(char *str)
{
	char qoute_type;
	int i;
	int single_qoute;
	int doble_qoute;

	single_qoute = 0;
	doble_qoute = 0;
	i = 0;
	while(str && str[i])
	{
		if (str[i] == '"')
			doble_qoute++;
		if (str[i] == 39)
			single_qoute++;
		i++;
	}
	if (!(single_qoute % 2) && single_qoute)
		qoute_type =  39;
	if (!(doble_qoute % 2) && doble_qoute)
		qoute_type =  '"';
	if (!(single_qoute % 2) && single_qoute && !(doble_qoute % 2) && doble_qoute)
		qoute_type = 11;
	i = 0;
	while(str && str[i])
	{
		if (qoute_type == 11 && (str[i] == '"' || str[i] == 39))
		{
			while(str && str[i])
			{
				i++;
				if ((str[i] == '"' || str[i] == 39) && str[i - 1] == str[i])
					break;
				
				if (str[i] == ' ' && str[i + 1] != '|')
					str[i] = '~';
			}
		}
		else if (str[i] == qoute_type)
		{
			while(str && str[i])
			{
				i++;
				if (str[i] == qoute_type)
					break;
				if (str[i] == ' ')
					str[i] = '~';
			}
		}
		if (!str[i])
			break;
		i++;
	}
	return str;
}

void	get_the_right_forma(char *ncoom, t_list **ptr)
{
	char *holder;
	int qoute_numb;
	int dqoute_numb;
	int i;
	int j;
	
	i = 0;
	holder = malloc(sizeof(char) * ft_strlen(ncoom));
	*ptr = malloc(sizeof(t_list));
	(*ptr)->error = 0;
	*ptr = NULL;
	while(ncoom && ncoom[i])
	{
		j = 0;
		qoute_numb = 0;
		dqoute_numb = 0;
		while(ncoom[i] && pipe_checker(ncoom, i, qoute_numb, dqoute_numb))
		{
			if (ncoom[i] == '"')
			{
				while(ncoom[i] && ncoom[i] != '"')
					holder[j++] = ncoom[i++];
				// if (ncoom[i] == '"')
				// 	holder[j++] = '"';
			}
			else if (ncoom[i] == 39)
			{
				while(ncoom[i] && ncoom[i] != 39)
					holder[j++] = ncoom[i++];
				// if (ncoom[i] == 39)
				// 	holder[j++] = 39;
			}
			if (ncoom[i])
				holder[j++] = ncoom[i++];
		}
		if (ncoom[i] == '|')
		{
			holder[j++] = '|';
			i++;
		}
		holder[j] = 0;
		holder = leave_it_for_me(holder);
		// printf("before[%s]\n",holder);
		nodepush(ptr, holder, 1);
	}
		qoutes_remover(ptr);

}

void readl_to_parse()
{
	t_list *ptr;
	t_var *var;
	int i;
	char *line;
	char *ncoom;

	ncoom = NULL;
	var = malloc(sizeof(t_var));
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
		while(ptr)
		{
			x = 0;
			printf("-------------------\n");
			printf("command=[%s]\n",ptr->command);
			while(ptr->arg[x])
				printf("arg=[%s]\n",ptr->arg[x++]);
			printf("operator=[%c]\n",ptr->operator);
			printf("error=[%d]\n",ptr->error);
			ptr = ptr->link;
		}
	}
}