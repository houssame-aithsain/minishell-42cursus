/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 07:49:38 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/15 16:30:19 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_r(char *str, int ex_s)
{
	t_e.exit_status = ex_s;
	write(2, str, ft_strlen(str));
}

int	print_error(t_bash *ptr)
{
	while (ptr)
	{
		if (ptr->error == S_QUOTE || ptr->error == D_QUOTE)
		{
			print_r("minishell: unexpected EOF while looking for matching\n", 2);
			return (1);
		}
		else if (ptr->error == PIPE || ptr->error == BACK_SLASH
			|| ptr->error == SEMICOLON || ptr->error == S_ERROR
			|| ptr->error == RD_ERROR || ptr->error == S_RD_ERROR)
		{
			print_r("minishell: syntax error\n", 2);
			return (1);
		}
		else if (ptr->error == NSFOD)
		{
			print_r("minishell: No such file or directory\n", 2);
			return (127);
		}
		ptr = ptr->link;
	}
	return (0);
}
