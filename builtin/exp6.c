/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp6.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:06:38 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:51 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getvalue_for_qst(char *content)
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
	value = ft_get_v_for_value_for_qst(content, j);
	return (value);
}

t_list_export	*ft_lstnew_mod_for_qst(char *content)
{
	t_list_export	*ls;
	char			*key;
	char			*value;
	char			*declare;

	ls = malloc(sizeof(t_list_export));
	declare = "declare -x ";
	key = ft_getkey(content);
	value = ft_getvalue_for_qst(content);
	if (!ls)
		return (0);
	ls->key = key;
	ls->value = value;
	declare = ft_strjoin_bb(declare, ls->key);
	if (ft_detect_equal(ls->key, content) == 0)
		declare = ft_strjoin(declare, "=");
	if (ls->value)
		declare = ft_strjoin(declare, ls->value);
	ls->content = declare;
	ls->next = NULL;
	return (ls);
}

t_list_export	*ft_create_export_lst(char **env)
{
	t_list_export	*node;
	t_list_export	*exp;
	int				i;

	i = 0;
	exp = NULL;
	node = ft_lstnew_mod("?=0");
	ft_lstadd_back_export(&exp, node);
	while (env[i])
	{
		node = ft_lstnew_mod(env[i]);
		ft_lstadd_back_export(&exp, node);
		i++;
	}
	return (exp);
}

void	ft_print_lst(t_list_export *la)
{
	unsigned int	i;

	i = 0;
	while (la)
	{
		if (la->key[0] == '?')
			la = la->next;
		else
		{
			while (la->content[i])
			{
				if ((i > (ft_strlen("declare -x ") + ft_strlen(la->key) + 1)
						&& i < (ft_strlen(la->content) - 1))
					&& (la->content[i] == '"' || la->content[i] == '$'))
					printf("\\");
				printf("%c", la->content[i]);
				i++;
			}
			la = la->next;
			i = 0;
			printf("\n");
		}
	}
}

int	detect_equal(char *val, char *key)
{
	int	i;

	i = 0;
	while (val[i])
	{
		if (val[i] == key[i])
			i++;
		break ;
	}
	if (val[i] == '=')
		return (1);
	return (0);
}
