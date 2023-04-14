/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readl_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:33:53 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/04/14 18:41:06 by hait-hsa         ###   ########.fr       */
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

char	*parse_input(char *line)
{
	int		j;
	int		i;
	int		index;
	int		pipe_count;
	int		copy_count;
	int		valid_quote;
	int		quote_type;
	int		if_quote;
	int		quote_count;
	char	*parsed_arr;
	char	quote_holder;

	i = 0;
	j = 0;
	index = 0;
	if_quote = 0;
	valid_quote = 0;
	copy_count = 0;
	pipe_count = 0;
	if (!ft_check_s_qoute(line))
		return "ERROR: missing a quote!\n";
	parsed_arr = malloc(ft_strlen(line) + 1);
	while(line && line[i])
	{
		if (!pipe_count)
			if(line[i] && line[i] == '|' && (((line[i + 1] && line[i + 1] == 39) || (line[i - 1] && line[i - 1] == 39))
				|| ((line[i + 1] && line[i + 1] == '"') || (line[i - 1] && line[i - 1] == '"'))))
				parsed_arr[j++] = '^';
		if (line[i] && (line[i] == '"' || line[i] == 39) && (ft_memcmp(line + i, "echo", 4 || ft_memcmp(line + i, "ECHO", 4))))
		{
			if (line[i] == '"')
				quote_type = 1;
			else
				quote_type = 2;
			quote_count = i;
			quote_count++;
			valid_quote++;
			if_quote = check_quotes(line, quote_count, quote_type);
			while(line[quote_count] && if_quote && (line[quote_count] != '"' || line[quote_count] != 39))
			{
				if (line[quote_count] == '"' || line[quote_count] == 39)
					break;
				if (line[quote_count] == ' ' && (valid_quote % 2))
					line[quote_count] = '^';
				quote_count++;
			}
			i++;
		}
		else
		{
			if (!ft_memcmp(line + i, "echo", 4) || !ft_memcmp(line + i, "ECHO", 4))
			{
				while(line[i] && line[i] != '|')
					parsed_arr[j++] = line[i++];
			}
			else if (!ft_memcmp(line + i, "grep", 4) || !ft_memcmp(line + i, "GREP", 4))
			{
				while(line[i] && copy_count < 4)
				{
					parsed_arr[j++] = line[i++];
					copy_count++;
				}
				if ((ft_quote_type(line, i)) == 1)
					quote_holder = '"';
				else if ((ft_quote_type(line, i)) == 2)
					quote_holder = 39;
				else if ((ft_quote_type(line, i)) == 3)
					quote_holder = ' ';
				parsed_arr[j++] = line[i++];
				while(line[i] && line[i] != quote_holder)
					parsed_arr[j++] = line[i++];
			}
			else
				parsed_arr[j++] = line[i++];
		}
	}
	parsed_arr[j] = 0;
	return parsed_arr;
}

void readl_and_parse()
{
	int i;
	char *line;
	char *ncoom;

	ncoom = NULL;
	while (TRUE)
	{
		i = 0;
		line = NULL;
		line = readline("minishell$> ");
		ncoom = parse_input(line);
		printf("str: %s\n",ncoom);
	}
}