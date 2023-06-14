/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirv2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:12:48 by gothmane          #+#    #+#             */
/*   Updated: 2023/06/13 19:27:30 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_access_red(char *file)
{
	int	r;

	r = access(file, F_OK | R_OK);
	if (r == 0)
		return (1);
	else
		return (-1);
}

int	ft_check_access_redir(t_bash *cmd)
{
	int	i;
	int	fd;

	i = 0;
	fd = -1;
	if (!cmd)
		return (404);
	while (cmd->redirection[i])
	{
		if (ft_strncmp(cmd->redirection[i], ">", 2) == 0)
		{
			if (ft_access_red(cmd->file[i]) == -1)
				fd = open(cmd->file[i], O_CREAT , 0664);
			else
				fd = open(cmd->file[i], O_TRUNC, NULL);
			close(fd);
		}
		
		i++;
	}
	return (1);
}

int	ft_check_access_inred(t_bash *cmd)
{
	int	i;
	int	fd;
	int	counter;

	i = 0;
	fd = -1;
	counter = 0;
	if (!cmd)
		return (404);
	while (cmd->redirection[i])
	{
		if (ft_strncmp(cmd->redirection[i], "<", 2) == 0)
		{
			counter++;
			if (ft_access_red(cmd->file[i]) == -1)
			{
				printf("ERROR FILE NOT FOUND %s\n", cmd->file[i]);
				return (-1);
			}
		}
		i++;
	}
	if (counter == 0)
		return (-2);
	return (1);
}

int	ft_count_redir_type(t_bash *cmd, char *c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (cmd->redirection[i])
	{
		if (ft_strncmp(cmd->redirection[i], c, 2) == 0)
			j++;
		i++;
	}
	return (j);
}

int	ft_check_cmd(t_bash *cmd, t_list_env *env)
{
	char	*path_sp;
	int		cc;

	cc = _ft_check_builtin_return_int(cmd);
	path_sp = ft_check_access_cmd(cmd, env);
	if (!path_sp && ft_check_slash_dot(cmd, env) != 1 && cc != 1)
		return (0);
	return (1);
}

typedef struct t_redir_in
{
	t_bash	*last_c;
	int		i;
	int		last;
	int		ds;
	char	*ss;
	int		p;
}			s_redir_in;

int	_ft_first_condition_in(t_bash *cmd, s_redir_in *ins)
{
	if (ft_strcmp((*ins).last_c->redirection[(*ins).i], "<") == 0 || ft_strcmp((*ins).last_c->redirection[(*ins).i], "<<") == 0)
	{
		if ((((*ins).last_c->file[(*ins).i] && (*ins).last_c->file[(*ins).i][0] == 4) || (*ins).last_c->error == 10))
			return (-18);
		if ((ft_strncmp((*ins).last_c->redirection[(*ins).i], "<", 2) == 0 && access((*ins).last_c->file[(*ins).i], F_OK) != 0))
			return (-400);
		(*ins).last = (*ins).i;
	}
	return (1);
}
int	_ft_second_condition_in(t_bash *cmd, s_redir_in *ins)
{
	int ss = access((*ins).last_c->file[(*ins).last], R_OK);
	if (ss == 0)
	{
		(*ins).ds = open((*ins).last_c->file[(*ins).last], O_RDONLY);
		if ((*ins).ds == -1)
			return (-400);
		return ((*ins).ds);
	}
	else
	{
		printf("minishell: %s: Permission denied\n", (*ins).last_c->file[(*ins).last]);
		exit_status = 1;
		exit(1);
		return (-9090);
	}
	return (1);
}

void	ft_init_redir_in(t_bash *cmd, s_redir_in *ins)
{
	(*ins).i = 0;
	(*ins).ds = 0;
	(*ins).last = 0;
	(*ins).last_c = cmd;
	(*ins).p = 0;
	(*ins).ss = NULL;
}
int	_ft_check_last_in(t_bash *cmd)
{
	s_redir_in	ins;

	ft_init_redir_in(cmd, &ins);
	while (ins.last_c->redirection[ins.i])
	{
		ins.p = _ft_first_condition_in(cmd, &ins);
		if (ins.p != 1)
			return (ins.p);
		ins.i++;
	}
	if (ins.last_c->redirection[ins.last] && ft_strcmp(ins.last_c->redirection[ins.last], "<") == 0)
	{
		ins.p = _ft_second_condition_in(cmd, &ins);
		if (ins.p != 1)
			return (ins.p);
	}
	if (ins.last_c->redirection[ins.last] && ft_strcmp(ins.last_c->redirection[ins.last], "<<") == 0)
	{
		ins.ss = ft_strjoin(ins.last_c->file[ins.last], ".tmp");
		return (open(ins.ss, O_RDONLY));
	}
	return (-404);
}

int	_ft_check_access_infile(char *red, char *file)
{
	if (ft_strcmp(red, "<") == 0)
	{
		if (access(file, R_OK | F_OK) == -1)
			return (-1);
	}
	return (-4);
}

typedef struct	t_redir_out
{
	t_bash	*last_c;
	int		i;
	int		ds;
	int		hold_a;
	int		hold_b;
}				s_redir_out;


int	_ft_first_cond_out(t_bash *cmd, s_redir_out *out)
{
	if (((*out).last_c->file[(*out).i] && (*out).last_c->file[(*out).i][0] == 4) || (*out).last_c->error == 10)
		return (-18);
	if (ft_strcmp((*out).last_c->redirection[(*out).i], ">") == 0)
	{
		(*out).ds = open((*out).last_c->file[(*out).i], O_CREAT | O_RDWR | O_TRUNC, 0777);
		if ((*out).ds == -1)
		{
			printf("minishell: %s: Permission denied\n", (*out).last_c->file[(*out).i]);
			exit_status = 1;
			exit(1);
			return (-9090);
		}
	}
	return (1);
}

int	_ft_second_cond_out(t_bash *cmd, s_redir_out *out)
{
	printf("minishell: %s: Permission denied\n", (*out).last_c->file[(*out).i]);
	exit_status = 1;
	exit(1);
	return (-9090);
}

void	_ft_init_out_var(s_redir_out *out, t_bash *cmd)
{
	(*out).i = 0;
	(*out).ds = -404;
	(*out).last_c = cmd;
	(*out).hold_a = 0;
	(*out).hold_b = 0;
}

int	_ft_check_last_out(t_bash *cmd)
{
	s_redir_out	out;

	_ft_init_out_var(&out, cmd);
	while (out.last_c->redirection[out.i])
	{
		if ( _ft_check_access_infile(out.last_c->redirection[out.i], out.last_c->file[out.i]) == -1)
			break;
		else if (ft_strcmp(out.last_c->redirection[out.i], ">") == 0 || ft_strcmp(out.last_c->redirection[out.i], ">>") == 0)
		{
			out.hold_a = _ft_first_cond_out(cmd, &out);
			if (out.hold_a != 1)
				return (out.hold_a);
			else if (ft_strcmp(out.last_c->redirection[out.i], ">>") == 0)
			{
				out.ds = open(out.last_c->file[out.i], O_CREAT | O_RDWR | O_APPEND, 0777);
				if (out.ds == -1)
					_ft_second_cond_out(cmd, &out);
			}
		}
		out.i++;
	}
	return (out.ds);
}

typedef struct t_main_redir
{
	int 	s;
	int		k;
	char	*here_doc_string;
	int 	first_in;
	int		last_out;
}			s_main_redir;

void	ft_init_main_redir_vars(s_main_redir *mr, t_bash *cmd)
{
	(*mr).s = -1;
	(*mr).k = -1;
	(*mr).here_doc_string = NULL;
	(*mr).first_in = _ft_check_last_in(cmd);
	(*mr).last_out =  _ft_check_last_out(cmd);
}
void		ft_run_redir(t_bash *cmd, t_list_env *env, t_list_export *exp)
{
	s_main_redir mr;
	
	ft_init_main_redir_vars(&mr, cmd);
	if (mr.first_in == -18 || mr.last_out == -18)
	{
		write(2, "minishell: ambiguous redirect\n", ft_strlen("minishell: ambiguous redirect\n"));
        exit_status = 1;
        exit(1);
	}
	else if (mr.first_in == -404 && mr.last_out == -404)
        return ;
    else if (mr.first_in == -400)
    {
        // printf("NOT FOUND\n");
        printf("minishell: No such file or directory\n");
        exit_status = 1;
        exit(1);
    }
    else if (mr.first_in == -400 && mr.last_out == -404)
    {
        printf("minishell: ambiguous redirect\n");
        exit_status = 1;
        exit(1);
    }
    else if (mr.first_in == -404 && mr.last_out == -1)
    {
        printf("minishell: ambiguous redirect\n");
        exit_status = 1;
        exit(1);
    }
    else if (mr.first_in > 0)
    {
        // printf("DUPPED input\n");
        dup2(mr.first_in, STDIN_FILENO);
        close(mr.first_in);
    }
    if (mr.last_out > 0)
    {
        dup2(mr.last_out, STDOUT_FILENO);
        close(mr.last_out);
    }
}
