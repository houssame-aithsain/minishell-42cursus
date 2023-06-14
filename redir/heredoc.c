// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   heredoc.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/05/19 12:27:58 by gothmane          #+#    #+#             */
// /*   Updated: 2023/06/13 16:47:41 by gothmane         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../minishell.h"
// last v
int ft_heredocs_counter(char **redir)
{
	int i;
	int counter;
	int size_redir;

	i = 0;
	counter = 0;
	if (!redir)
		return (-404);
	size_redir = 0;
	while (redir[i])
	{
		if (ft_strcmp(redir[i], "<<") == 0)
			counter++;
		i++;
	}
	return (counter);
}

typedef struct t_heredoc_data
{
	int i;
	char *arr;
	char *eof;
	char *data_hd;
	int j;
	int k;
	int fd;
	char *temp;
} s_heredoc_data;

void ft_heredoc_init(s_heredoc_data *hd)
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

void	ft_sup_last_hd(s_heredoc_data *hd, t_bash *cmd, t_list_export *exp)
{
	(*hd).temp = ft_expand_in_heredoc((*hd).arr, exp);
	
	if ((*hd).temp && cmd->h_expn == 0 && ft_strcmp((*hd).eof, (*hd).arr) != 0)
	{
		if (!(*hd).data_hd)
			(*hd).data_hd = ft_strjoin_bb((*hd).data_hd, (*hd).temp);
		else
			(*hd).data_hd = ft_strjoin((*hd).data_hd, (*hd).temp);
		(*hd).data_hd = ft_strjoin((*hd).data_hd, "\n");
	}
	else
	{
		(*hd).data_hd = ft_strjoin((*hd).data_hd, (*hd).arr);
		(*hd).data_hd = ft_strjoin((*hd).data_hd, "\n");
	}
	free((*hd).temp);
}
int	ft_last_main_hd(s_heredoc_data *hd, t_bash *cmd, t_list_export *exp, char *eof)
{
	(*hd).arr = readline("> ");
	if (!(*hd).arr || ft_strcmp((*hd).arr, (*hd).eof) == 0)
	{
		(*hd).eof = ft_strjoin((*hd).eof, ".tmp");
		(*hd).fd = open((*hd).eof, O_CREAT | O_RDWR | O_TRUNC, 0777);
		cmd->fd_heredoc = (*hd).fd;
		write((*hd).fd, (*hd).data_hd, ft_strlen((*hd).data_hd));
		free((*hd).data_hd);
		free((*hd).eof);
		free((*hd).arr);
		return (0);
	}
	else if (ft_strcmp((*hd).arr, (*hd).eof) != 0)
		ft_sup_last_hd(hd, cmd, exp);
	free((*hd).arr);
	return (1);
}
int	ft_first_heredocs(s_heredoc_data *hd, t_bash *cmd, t_list_export *exp)
{
	(*hd).eof = ft_strdup(cmd->file[(*hd).i]);
	while (ft_strcmp(cmd->redirection[(*hd).i], "<<") == 0)
	{
		if ((*hd).k < ((*hd).j - 1))
		{
			while ((*hd).k < ((*hd).j - 1))
			{
				(*hd).arr = readline("> ");
				if (!(*hd).arr || ft_strcmp((*hd).arr, (*hd).eof) == 0)
				{
					(*hd).i++;
					free((*hd).eof);
					(*hd).eof = ft_strdup(cmd->file[(*hd).i]);
					(*hd).k++;
					free((*hd).arr);
					break;
				}
				free((*hd).arr);
			}
		}
		else if ((*hd).k == ((*hd).j - 1))
		{
			if (ft_last_main_hd(hd, cmd, exp, (*hd).eof) == 0)
				return (0);
		}
	}
	return (1);
}
char *ft_heredoc(t_bash *cmd, t_list_export *exp)
{
	s_heredoc_data hd;

	ft_heredoc_init(&hd);
	while (cmd && !cmd->redirection[0])
		cmd = cmd->link;
	hd.j = ft_heredocs_counter(cmd->redirection);
	while (cmd->redirection[hd.i] && hd.j != -404)
	{
		if (ft_strcmp(cmd->redirection[hd.i], "<<") == 0)
		{
			if (ft_first_heredocs(&hd, cmd, exp) == 0)
				return (0);
		}
		// close(fd);
		hd.i++;
	}
	free(hd.data_hd);
	return (0);
}

int ft_rm_quotes(char *str)
{
	int i;
	char *ptr = malloc(sizeof(char *) * ft_strlen(str) - 2);

	ptr = ft_substr(str, 1, ft_strlen(str) - 2);
	return (1);
}

int ft_check_dollar_sign(char *arg)
{
	int checker;
	int sa;

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

void ft_sup_exp_here_helper(char **ee, t_list_export *exp, int k, char **subbed, char **second)
{
	*second = ft_substr(*ee, (0), (k));
	free(*second);
	*second = ft_substr(get_val_for_a_specific_key(exp, *second), 1, ft_strlen(get_val_for_a_specific_key(exp, *second)) - 2);
	if (*second)
	{
		*subbed = ft_substr(*ee, k, ft_strlen(*ee));
		*second = ft_strjoin(*second, *subbed);
		free(*ee);
		*ee = *second;
		free(*subbed);
	}
	else
	{
		free(*ee);
		*ee = ft_strdup("");
		free(*second);
	}
}
char **ft_exp_here_helper(char *arg, t_list_export *exp)
{
	char **ee;
	char *second;
	int e;
	int k;
	char *subbed;

	e = 0;
	k = 0;
	ee = ft_split(arg, '$');
	if (!ee || ft_check_dollar_sign(arg) == 0)
	{
		ft_free_args(ee);
		return (NULL);
	}
	while (ee[e])
	{
		k = 0;
		while (ee[e][k] && ee[e][k] != 39 && ee[e][k] != ' ' && ee[e][k] != '-' && ee[e][k] != '"' && ee[e][k] != '$' && ee[e][k] != '*' && ee[e][k] != '@' &&
			   (ft_isdigit(ee[e][k]) || ft_isalpha(ee[e][k]) || ee[e][k] == '_' || ee[e][k] == '?'))
			k++;
		if (k > 0)
			ft_sup_exp_here_helper(&ee[e], exp, k, &subbed, &second);
		e++;
	}
	return (ee);
}

typedef struct t_exp_h
{
	int i;
	int e;
	char *joined;
	char **ee;
} s_exp_h;

void ft_exp_h_init(s_exp_h *exp)
{
	exp->e = 0;
	exp->i = 0;
	exp->ee = NULL;
	exp->joined = NULL;
}
char *ft_expand_in_heredoc(char *arg, t_list_export *ex)
{
	s_exp_h exp;

	ft_exp_h_init(&exp);
	if (arg)
	{
		exp.ee = ft_exp_here_helper(arg, ex);
		if (exp.ee && exp.ee[0])
		{
			exp.joined = ft_strdup(exp.ee[0]);
			free(exp.ee[0]);
		}
		else
			return (NULL);
		exp.e = 1;
		while (exp.ee[exp.e])
		{
			exp.joined = ft_strjoin(exp.joined, exp.ee[exp.e]);
			free(exp.ee[exp.e]);
			exp.e++;
		}
		free(exp.ee);
		return (exp.joined);
	}
	return (0);
}
