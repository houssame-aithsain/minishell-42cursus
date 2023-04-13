/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readl_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:33:53 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/04/13 21:07:36 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		valid;
	int		cout;
	int		check;
	int		count;
	int		j;
	int		i;
	int		index;
	char	*arr;

	i = 0;
	j = 0;
	index = 0;
	check = 0;
	valid = 0;
	arr = malloc(ft_strlen(line) + 1);
	while(line && line[i])
	{
		if (line[i] && (line[i] == '"' || line[i] == 39))
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