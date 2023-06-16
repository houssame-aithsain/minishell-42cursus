/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:02:46 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_v_for_value(char *content, int j)
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
	return (value);
}

char	*ft_getvalue(char *content)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	value = NULL;
	while (content[i])
	{
		if (content[i] == '=')
		{
			j = i;
			break ;
		}
		i++;
	}
	if (j == 0)
		return (0);
	value = ft_get_v_for_value(content, j);
	return (value);
}

char	*ft_strnew_bb(size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}

char	*ft_strjoin_bb(char *s1, char const *s2)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = ft_strnew_bb(s1_len + s2_len);
	if (!new_str)
		return (NULL);
	i = -1;
	j = -1;
	while (++i < s1_len)
		*(new_str + i) = *(s1 + i);
	while (++j < s2_len)
		*(new_str + i++) = *(s2 + j);
	*(new_str + i) = '\0';
	return (new_str);
}

int	ft_detect_equal(char *key, char *content)
{
	int	i;

	i = 0;
	if (key)
	{
		i = ft_strlen(key);
		if ((content && content[i] == '=')
			|| (content[i] == '+' && content[i + 1] == '='))
			return (0);
	}
	return (1);
}
