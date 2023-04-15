/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readl_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:33:53 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/04/15 18:28:00 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_s_qoute(char *line)
{
	int	i;
	int	s_qoute;
	int	d_qoute;

	i = 0;
	s_qoute = 0;
	d_qoute = 0;
	while(line && line[i])
	{
		if (line[i] == '"')
			s_qoute++;
		else if (line[i] == 39)
			d_qoute++;
		i++;
	}
	if ((s_qoute % 2) || (d_qoute % 2))
		return 0;
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
	if(line[var->i] && line[var->i] == '|'
		&& (((line[var->i + 1] && line[var->i + 1] == 39)
		|| (line[var->i - 1] && line[var->i - 1] == 39))
		|| ((line[var->i + 1] && line[var->i + 1] == '"')
		|| (line[var->i - 1] && line[var->i - 1] == '"'))))
	{
		var->parsed_arr[var->j] = '^';
		var->j += 1;
	}
		
}

void	ft_test1(char *line, t_var *var)
{
	var->copy_count = 0;
	if (if_grep(line , var->i, ECHO))
	{
		while(line[var->i] && line[var->i] != '|')
			var->parsed_arr[var->j++] = line[var->i++];
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
		if (line[var->i] != ' ')
			var->parsed_arr[var->j++] = '^';
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

void readl_to_parse()
{
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
		printf("str: %s\n",ncoom);
	}
}