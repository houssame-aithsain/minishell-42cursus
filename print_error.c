/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 07:49:38 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/12 00:37:05 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int print_error(t_bash *ptr)
{
	while(ptr)
	{
		if (ptr->error == S_QUOTE)
		{
			// write(2,"ERROR\n",6);
			printf("minishell: unexpected EOF while looking for matching\n");
			exit_status = 2;
			return 1;
		}
		else if (ptr->error == D_QUOTE)
		{
			// write(2,"ERROR\n",6);
			printf("minishell: unexpected EOF while looking for matching\n");
			exit_status = 2;
			return 1;
		}
		else if (ptr->error == PIPE)
		{
			// write(2,"ERROR\n",6);
			printf("minishell: syntax error\n");
			exit_status = 2;
			return 1;
		}
		else if (ptr->error == BACK_SLASH)
		{
			// write(2,"ERROR\n",6);
			printf("minishell: syntax error\n");
			exit_status = 2;
			return 1;
		}
		else if (ptr->error == SEMICOLON)
		{
			// write(2,"ERROR\n",6);
			printf("minishell: syntax error\n");
			exit_status = 2;
			return 1;
		}
		else if (ptr->error == S_ERROR)
		{
			// write(2,"ERROR\n",6);
			printf("minishell: syntax error\n");
			exit_status = 2;
			return 1;
		}
		else if (ptr->error == RD_ERROR)
		{
			// write(2,"ERROR\n",6);
			printf("minishell: syntax error\n");
			exit_status = 2;
			return 1;
		}
		else if (ptr->error == S_RD_ERROR)
		{
			// write(2,"ERROR\n",6);
			printf("minishell: syntax error\n");
			exit_status = 2;
			return 1;
		}
		else if (ptr->error == NSFOD)
		{
			// write(2,"ERROR\n",6);
			printf("minishell: No such file or directory\n");
			exit_status = 2;
			return 127;
		}
		// else if (ptr->error == AR)
		// {
		// // 	// write(2,"ERROR\n",6);
		// 	printf("minishell: ambiguous redirect\n");
		// 	exit_status = 2;
		// 	return 1;
		// }
		ptr = ptr->link;
	}
	return 0;
}