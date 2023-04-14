/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readl_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:33:53 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/04/14 01:48:06 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_grep(char *line, int i)
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

int	ft_checker(char *line, int count, int cout)
{
	char x;

	if (cout == 1)
		x = '"';
	else
		x = 39;
	while(line && line[count])
	{
		if (line[count++] == x)
			return 1;
	}
	return 0;
}

char	*ft_parse(char *line)
{
	int		pipe;
	int		copy;
	int		valid;
	int		cout;
	int		check;
	int		count;
	int		j;
	int		i;
	int		index;
	char	*arr;
	char	swit;

	i = 0;
	j = 0;
	index = 0;
	check = 0;
	valid = 0;
	copy = 0;
	pipe = 0;
	arr = malloc(ft_strlen(line) + 1);
	while(line && line[i])
	{
		if (!pipe)
			if(line[i] && line[i] == '|' && (((line[i + 1] && line[i + 1] == 39) || (line[i - 1] && line[i - 1] == 39))
				|| ((line[i + 1] && line[i + 1] == '"') || (line[i - 1] && line[i - 1] == '"'))))
				arr[j++] = '^';
		if (line[i] && (line[i] == '"' || line[i] == 39) && (ft_memcmp(line + i, "echo", 4 || ft_memcmp(line + i, "ECHO", 4))))
		{
			if (line[i] == '"')
				cout = 1;
			else
				cout = 2;
			count = i;
			count++;
			valid++;
			check = ft_checker(line, count, cout);
			while(line[count] && check && (line[count] != '"' || line[count] != 39))
			{
				if (line[count] == '"' || line[count] == 39)
					break;
				if (line[count] == ' ' && (valid % 2))
					line[count] = '^';
				count++;
			}
			i++;
		}
		else
		{
			if (!ft_memcmp(line + i, "echo", 4) || !ft_memcmp(line + i, "ECHO", 4))
			{
				while(line[i] && line[i] != '|')
					arr[j++] = line[i++];
			}
			else if (!ft_memcmp(line + i, "grep", 4) || !ft_memcmp(line + i, "GREP", 4))
			{
				while(line[i] && copy < 4)
				{
					arr[j++] = line[i++];
					copy++;
				}
				if ((ft_grep(line, i)) == 1)
					swit = '"';
				else if ((ft_grep(line, i)) == 2)
					swit = 39;
				else if ((ft_grep(line, i)) == 3)
					swit = ' ';
				arr[j++] = line[i++];
				while(line[i] && line[i] != swit)
					arr[j++] = line[i++];
			}
			else
				arr[j++] = line[i++];
		}
	}
	arr[j] = 0;
	return arr;
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
		ncoom = ft_parse(line);
		printf("str: %s\n",ncoom);
	}
}