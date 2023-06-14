/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readl_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-hsa <hait-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:33:53 by hait-hsa          #+#    #+#             */
/*   Updated: 2023/06/14 11:06:52 by hait-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void readl_to_parse(char **env)
{
	t_bash *ptr;
	t_bash *tmp;
	t_var *var;
	int i;
	char *line;
	t_list_export *exp_ls;
	t_list_env *env_ls;

	env_ls = put_env_to_ls(env);
	exp_ls = ft_create_export_lst(env);
	t_list_env *as = env_ls;
	while (env_ls)
	{
		if (ft_strcmp("SHLVL", env_ls->key) == 0)
		{
			free(env_ls->value);
			env_ls->value = ft_itoa(ft_atoi(env_ls->value) + 1);
			free(env_ls->content);
			env_ls->content = env_ls->key;
			env_ls->content = ft_strjoin(env_ls->content, "=");
			env_ls->content = ft_strjoin(env_ls->content, env_ls->value);
		}
		env_ls = env_ls->next;
	}
	int fd = dup(0);
	env_ls = as;
	while (TRUE)
	{
		line = NULL;
		ptr = NULL;
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
		rl_catch_signals = 0;
		dup2(fd, 0);
		r = 1;
		line = readline("minishell$> ");
		if (!line)
		{
			if (rl_catch_signals == 1)
			{
				exit_status = 1;
				continue ;
			}
			exit(exit_status);
		}
		add_history(line);
		list_parse(line, &ptr, &env_ls, &exp_ls);
		free(line);
		//=========================>ptr is the head bitch!<===========================//
		// ft_infile_redir(ptr, env_ls);
		// printf("WA ANA KHAREJ\n");
		if (ptr && !print_error(ptr))
		{
			n_pipe(ptr, &env_ls, &exp_ls);
			// ft_run_redir(ptr, env_ls, exp_ls);
			// ft_check_builtins(ptr, env_ls, exp_ls);
			// // ft_heredoc(ptr, exp_ls);
			// if (ft_strcmp(ptr->command, "export") == 0)
			// {
			// 	ft_export(&exp_ls, ptr->arg, &env_ls);
			// 	if (!ptr->arg[0])
			// 		ft_print_lst(exp_ls);
			// }

			// else if (ft_strcmp(ptr->command, "echo") == 0)
			// 	ft_echo(ptr->arg);
			// else if (ft_strcmp(ptr->command, "pwd") == 0)
			// 	ft_pwd();
			// else if (ft_strcmp(ptr->command, "cd") == 0)
			// {
			// 	if (ptr->arg)
			// 		ft_cd(ptr->arg[0]);
			// }
			// else if (ft_strcmp(ptr->command, "unset") == 0)
			// {
			// 	ft_unset(&env_ls, &exp_ls, ptr->arg[0]);
			// 	ft_print_lst_env(env_ls);
			// }
			// else if (ft_strcmp(ptr->command, "env") == 0)
			// {
			// 	ft_print_lst_env(env_ls);
			// }
			// else
			// {
			// 	// ft_final_exec_sgl_cmd(ptr, env_ls);
			// 	// ft_piping_bash(ptr, env_ls);
			// 	// ft_open_files(ptr);

			// }
		}
		// printf("(%s)\n",ncoom);
		// free(line);
		// free(ncoom);
		// int x = 0;
		// int h = 0;
		// int f = 0;
		// while (ptr)
		// {
		// 	x = 0;
		// 	h = 0;
		// 	f = 0;
		// 	printf("-------------------\n");
		// 	printf("command=[%s]\n", ptr->command);
		// 	while (ptr->arg[x])
		// 		printf("arg=[%s]\n", ptr->arg[x++]);
		// 	while (ptr->redirection[h])
		// 		printf("redirection=[%s]\n", ptr->redirection[h++]);
		// 	while (ptr->file[f])
		// 		printf("file=[%s]\n", ptr->file[f++]);
		// 	printf("operator=[%c]\n", ptr->op);
		// 	printf("error=[%d]\n", ptr->error);
		// 	ptr = ptr->link;
		// }
		while(ptr)
		{
			free(ptr->command);
			i  = 0;
			while(ptr->file && ptr->file[i])
				free(ptr->file[i++]);
			free(ptr->file);
			i = 0;
			while(ptr->redirection && ptr->redirection[i])
				free(ptr->redirection[i++]);
			free(ptr->redirection);
			i = 0;
			while(ptr->arg && ptr->arg[i])
				free(ptr->arg[i++]);
			free(ptr->arg);
			tmp = ptr->link;
			free(ptr);
			ptr = tmp;
		}
		// printf("-------------LEAKS------------\n");
		// system("leaks minishell");
		// printf("-------------END-L------------\n");
	}
}