/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 19:42:55 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/04/01 20:54:28 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv)
{
	int i;
	char *line;
	char **ncoom;
	while(1)
	{
		line = readline("minishell$> ");
		ncoom = ft_split(line, ' ');
		printf("%s\n",ncoom[1]);
	}
}