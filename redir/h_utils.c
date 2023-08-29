/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:26:07 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/15 16:21:55 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exp_h_init(t_exp_h *exp)
{
	exp->e = 0;
	exp->i = 0;
	exp->ee = NULL;
	exp->joined = NULL;
}

int	ft_rm_quotes(char *str)
{
	char	*ptr;

	(void)ptr;
	ptr = malloc(sizeof(char *) * ft_strlen(str) - 2);
	ptr = ft_substr(str, 1, ft_strlen(str) - 2);
	return (1);
}

int	ft_check_dollar_sign(char *arg)
{
	int	checker;
	int	sa;

	sa = 0;
	checker = 0;
	while (arg[sa])
	{
		if (arg[sa] == '$')
			checker = 1;
		sa++;
	}
	return (checker);
}

void	ft_heredoc_init(t_heredoc_data *hd)
{
	(*hd).i = 0;
	(*hd).arr = NULL;
	(*hd).eof = NULL;
	(*hd).data_hd = ft_strdup("");
	(*hd).temp = NULL;
	(*hd).fd = -404;
	(*hd).k = 0;
	(*hd).j = 0;
}

void	ft_sup_exp_here_helper(char **ee, t_list_export *exp, int k,
	t_exp_helper *seh)
{
	seh->second = ft_substr(*ee, (0), (k));
	free(seh->second);
	seh->second = ft_substr(get_val_for_a_specific_key(exp, seh->second), 1,
			ft_strlen(get_val_for_a_specific_key(exp, seh->second)) - 2);
	if (seh->second)
	{
		seh->subbed = ft_substr(*ee, k, ft_strlen(*ee));
		seh->second = ft_strjoin(seh->second, seh->subbed);
		free(*ee);
		*ee = seh->second;
		free(seh->subbed);
	}
	else
	{
		free(*ee);
		*ee = ft_strdup("");
		free(seh->second);
	}
}
