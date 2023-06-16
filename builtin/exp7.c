/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp7.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:07:04 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getkey(char *content)
{
	int		i;
	char	*key;

	i = 0;
	key = NULL;
	while (content[i])
	{
		if (content[i] == '=' || content[i] == '+')
			break ;
		i++;
	}
	key = ft_substr(content, 0, i);
	return (key);
}

char	*ft_get_v_for_value_for_qst(char *content, int j)
{
	char	*value;
	char	*tmp;

	tmp = NULL;
	value = ft_strdup("\"");
	if (j > 0)
	{
		tmp = ft_substr(content, j + 1, ft_strlen(content));
		value = ft_strjoin(value, tmp);
		free(tmp);
	}
	value = ft_strjoin(value, "\"");
	free(content);
	return (value);
}
