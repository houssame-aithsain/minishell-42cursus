/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 07:26:57 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/14 10:59:54 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	__rd_errors(char *tmp, int *error, char quote_type, int i)
{
	if ((tmp[i] == '>' || tmp[i] == '<') && tmp[i] != quote_type)
		*error = RD_ERROR;
	else if ((tmp[i] == '>' || tmp[i] == '<'))
		i++;
	if ((tmp[i] == '>' || tmp[i] == '<'))
		*error = RD_ERROR;
	if (tmp[i] && tmp[i] == ' ')
	{
		while (tmp[i] && tmp[i] == ' ')
			i++;
		if (tmp[i] == '>' || tmp[i] == '<')
			*error = RD_ERROR;
	}
	if (tmp[i] == '|')
		*error = PIPE;
	if (!tmp[i])
		*error = S_RD_ERROR;
	if (tmp[i] == '"' || tmp[i] == 39)
	{
		if (tmp[i + 1] == '"' || tmp[i + 1] == 39)
		{
			i++;
			if (!tmp[i + 1] || tmp[i + 1] == ' ')
				*error = NSFOD;
		}
	}
	return (i);
}

int	_rd_errors(char *tmp, int *error, char quote_type, int i)
{
	if (tmp[i] == '>' || tmp[i] == '<')
	{
		quote_type = quote_t(tmp + i, '>', '<', 0);
		i = __rd_errors(tmp, error, quote_type, ++i);
	}
	else if (tmp[i] == '|')
	{
		i++;
		while (tmp[i] && tmp[i] == ' ')
			i++;
		if (!tmp[i] || tmp[i] == '|')
			*error = PIPE;
	}
	else
		i++;
	return (i);
}

void	_f_errors(char *tmp, int *error, int i)
{
	while (tmp && tmp[++i])
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
			break ;
	}
}

void	check_str_errors(char *tmp, int *error)
{
	int		i;
	char	quote_type;

	i = 0;
	while (tmp[i] && tmp[i] == ' ')
		i++;
	if (tmp[i] == '|')
		*error = PIPE;
	_f_errors(tmp, error, -1);
	i = 0;
	while (tmp && tmp[i])
		i = _rd_errors(tmp, error, quote_type, i);
}
