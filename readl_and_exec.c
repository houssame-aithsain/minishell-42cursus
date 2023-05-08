/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readl_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:33:53 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/05/08 21:13:56 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_s_qoute(char *line)
{
	char	qoute_type;
	int	i;
	int	s_qoute;
	int	d_qoute;

	i = 0;
	s_qoute = 0;
	d_qoute = 0;
	while(line && line[i])
	{
		if (if_grep(line, i, ECHO) || if_grep(line, i, GREP))
		{
			while(line[i])
			{
				if (line[i] == '|' && (!line[i + 1] || line[i + 1] == ' '))
				{
					i++;
					break;
				}
				i++;
			}
		}
		if (line[i] == '"')
			s_qoute++;
		else if (line[i] == 39)
			d_qoute++;
		if (line[i] == '|')
			break;
		i++;
	}
	if ((s_qoute % 2) || (d_qoute % 2))
		return (0);
	// if (s_qoute % 2)
	// 	qoute_type = 39;
	// else if (d_qoute %2)
	// 	qoute_type = '"';
	// check_qoute_inside(line, qoute_type);
	return 1;
}

int	ft_quote_type(char *line, int i)
{
	while(line[i])
	{
		if (line[i] == '"')
			return 1;
		else if (line[i] == 39)
			return 2;
		else if (line[i] == ' ')
			return 3;
		else
			return 0;
	}
	return 0;
}

int	check_quotes(char *line, int count, int cout)
{
	char quote_char;

	if (cout == 1)
		quote_char = '"';
	else
		quote_char = 39;
	while(line && line[count])
	{
		if (line[count++] == quote_char)
			return 1;
	}
	return 0;
}

int	if_n(char *line, int i)
{
	int qoute_numb;
	int	check;

	check = 0;
	qoute_numb = 0;
	while(line[i])
	{
		if (!ft_memcmp("-n", line + i, 2))
		{
			i += 2;
			if (check)
			{
				if (line[i] != '"' && line[i] != 39 && (qoute_numb % 2))
					return 0;
				else
				{
					while(line[i] && (line[i] == '"' || line[i] == 39))
						i++;
					if (line[i] == ' ' || !line[i])
						return 1;
					else
						return 0;
				}
			}
			else
				return 1;
		}
		if (line[i] == '"' || line[i] == 39)
		{
			check = 1;
			while(line[i] == '"' || line[i] == 39)
			{
				i++;
				qoute_numb++;
			}
			if (!ft_memcmp("-n", line + i, 2))
				i--;
			else
				return 0;
		}
		i++;
	}
	return 0;
}

void	ft_echo_flag(char *line, t_var *var)
{
	int copy;

	// printf("yeah!\n");
	// 	exit(0);
	// copy = 0;
	// if(!ft_memcmp("-n", line + var->i, 2))
	// {
	// 	while(line[var->i] && copy < 2)
	// 	{
	// 		var->parsed_arr[var->j++] = line[var->i++];
	// 		copy++;
	// 	}
	// }
	// printf("|%s|\n",line + var->i);
	copy = 0;
	while(line[var->i] && (line[var->i] == '"' || line[var->i] == 39 || line[var->i] == ' '))
		var->i++;
	// var->parsed_arr[var->j++] = ' ';
	if(!ft_memcmp("-n", line + var->i, 2))
	{
		while(line[var->i] && copy < 2)
		{
			var->parsed_arr[var->j++] = line[var->i++];
			copy++;
		}
	}
	while(line[var->i] && (line[var->i] == '"' || line[var->i] == 39))
		var->i++;
	// printf("%s|\n",var->parsed_arr);
	// exit(0);
}

void	ft_equale(char *line, t_var *var)
{
	int quote_type;
	var->parsed_arr[var->j++] = line[var->i];
	if (line[++var->i] == ' ')
		var->parsed_arr[var->j++] = '^';
	else if (line[var->i] == '"' || line[var->i] == 39)
	{
		if (ft_quote_type(line, var->i) == 1)
			quote_type = '"';
		else if ((ft_quote_type(line, var->i)) == 2)
			quote_type = 39;
		var->parsed_arr[var->j++] = line[var->i++];
		while(line[var->i] && line[var->i] != quote_type)
			var->parsed_arr[var->j++] = line[var->i++];
		var->parsed_arr[var->j++] = line[var->i++];
	}
	else
	{
		while(line[var->i] && line[var->i] != ' ')
			var->parsed_arr[var->j++] = line[var->i++];
		while(line[var->i] && line[var->i] == ' ')
			var->i++;
		if (line[var->i])
			var->parsed_arr[var->j++] = '^';
	}
}

void	ft_pipe_handler(char *line, t_var *var)
{
	if(line[var->i] && line[var->i] == '|' && (!line[var->i + 1]))
		printf("pipe error!\n");
}

void	ft_test1(char *line, t_var *var)
{
	int echo;

	echo = 0;
	var->copy_count = 0;
	if (if_grep(line , var->i, ECHO))
	{
		while(line[var->i] && line[var->i] != '|')
		{
			if (echo >= 5)
				if(if_n(line, var->i))
					ft_echo_flag(line, var);
			// printf("nope!\n");
			// 	exit(0);
			var->parsed_arr[var->j++] = line[var->i++];
			echo++;
		}
		if (line[var->i] == '|')
		{
			var->parsed_arr[var->j++] = '|';
			var->i++;
		}
		if (line[var->i] == '"')
		{
			var->parsed_arr[var->j++] = '"';
			var->i++;
		}
		if (line[var->i] == 39)
		{
			var->parsed_arr[var->j++] = 39;
			var->i++;
		}
	}
	else if (if_grep(line, var->i, GREP))
	{
		while(line[var->i] && var->copy_count < 4)
		{
			var->parsed_arr[var->j++] = line[var->i++];
			var->copy_count++;
		}
		// if (line[var->i] != ' ')
		// 	var->parsed_arr[var->j++] = '^';
		if ((ft_quote_type(line, var->i+1)) == 1)
			var->quote_holder = '"';
		else if ((ft_quote_type(line, var->i+1)) == 2)
			var->quote_holder = 39;
		else if ((ft_quote_type(line, var->i+1)) == 3)
			var->quote_holder = ' ';
		var->parsed_arr[var->j++] = line[var->i++];
		var->parsed_arr[var->j++] = line[var->i++];
		while(line[var->i] && line[var->i] != var->quote_holder)
			var->parsed_arr[var->j++] = line[var->i++];
		var->parsed_arr[var->j++] = var->quote_holder;
	}
	else
		var->parsed_arr[var->j++] = line[var->i++];
}

void	ft_test(char *line, t_var *var)
{
	if (if_grep(line, var->i, ECHO_CHECK))
	{
		if (line[var->i] == '"')
			var->quote_type = 1;
		else
			var->quote_type = 2;
		var->quote_count = var->i;
		var->quote_count++;
		var->valid_quote++;
		var->if_quote = check_quotes(line, var->quote_count, var->quote_type);
		while(ft_loop(line, var))
		{
			if (line[var->quote_count] == '"' || line[var->quote_count] == 39)
				break;
			if (line[var->quote_count] == ' ' && (var->valid_quote % 2))
				line[var->quote_count] = '^';
			var->quote_count++;
		}
		var->i++;
	}
	else
		ft_test1(line, var);
}

char	*parse_input(char *line, t_var *var)
{
	var->i = 0;
	var->j = 0;
	var->index = 0;
	var->if_quote = 0;
	var->valid_quote = 0;
	var->pipe_count = 0;
	if (!ft_check_s_qoute(line))
		return "ERROR: missing a quote!\n";
	var->parsed_arr = malloc(ft_strlen(line) + 10);
	while(line && line[var->i])
	{
		
		if (line[var->i] == '=')
			ft_equale(line, var);
		if (!var->pipe_count)
			ft_pipe_handler(line, var);
		ft_test(line, var);
	}
	var->parsed_arr[var->j] = 0;
	return var->parsed_arr;
}

void	get_the_right_forma(char *ncoom, t_list **ptr)
{
	char *holder;
	int i;
	int j;
	
	i = 0;
	holder = malloc(sizeof(char) * ft_strlen(ncoom));
	*ptr = malloc(sizeof(t_list));
	*ptr = NULL;
	while(ncoom && ncoom[i])
	{
		j = 0;
		while(ncoom[i] && ncoom[i] != '|')
			holder[j++] = ncoom[i++];
		if (ncoom[i] == '|')
		{
			holder[j++] = '|';
			i++;
		}
		holder[j] = 0;
		// printf("holder = %s\n", holder);
		nodepush(ptr, holder, 1);
	}

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
		ncoom = parse_input(line, var);
		get_the_right_forma(ncoom, &ptr);


		// =========================>ptr is the head bitch!<===========================//

		// printf("(%s)\n",ncoom);
		// free(line);
		// free(ncoom);
		// int x = 0;
		// while(ptr)
		// {
		// 	x = 0;
		// 	printf("-------------------\n");
		// 	printf("command=[%s]\n",ptr->command);
		// 	while(ptr->arg[x])
		// 		printf("arg=[%s]\n",ptr->arg[x++]);
		// 	printf("operator=[%c]\n",ptr->operator);
		// 	ptr = ptr->link;
		// }
	}
}