/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_d_sig.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 06:23:08 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/16 15:42:36 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler(int sig_t)
{
	if (sig_t == SIGINT)
	{
		if (t_e.r)
			printf("\n");
		t_e.rl_catch_signals = 1;
		t_e.exit_status = 130;
		t_e.r = 0;
		close(0);
	}
	if (sig_t == SIGQUIT)
	{
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
}
