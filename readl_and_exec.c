/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readl_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:33:53 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/04/01 21:35:03 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	readl_and_exec()
{
	char *line;
	char **ncoom;
	char *envp;
	envp = "PATH=/usr/bin";
	while(1)
	{
		line = readline("minishell$> ");
		ncoom = ft_split(line, ' ');
		printf("%s\n",ncoom[0]);
		execve("/bin/ls", ncoom, &envp);
	}
}