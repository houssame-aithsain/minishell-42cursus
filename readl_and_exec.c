/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readl_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:33:53 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/04/12 22:03:49 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void readl_and_exec()
{
	int i;
	char *line;
	char **ncoom;
	char env[14] = "PATH=/usr/bin\0";
	char *envp;

	ncoom = NULL;
	envp = env;
	while (TRUE)
	{
		i = 0;
		line = NULL;
		line = readline("minishell$> ");
		ncoom = ft_split(line, ' ');
		while (ncoom && ncoom[i])
			printf("%s ", ncoom[i++]);
		printf("\n");
		free(ncoom);
		free(line);
	}
}