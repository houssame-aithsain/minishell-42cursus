/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 22:09:30 by gothmane          #+#    #+#             */
/*   Updated: 2023/05/15 20:25:10 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ft_echo
void ft_echo(char **str)
{
    int i;
    int n;

    n = 0;
    i = 0;
    while (str[i])
    {
        if (((n != 1) && (i == 0) && str[i][0] == '-' && str[i][1] == 'n'))
            n = 1;
        else
        {
            if (n == 1 && ft_strncmp(str[i], "-n", 2) == 0)
                i++;
            else
            {
                printf("%s", str[i]);
                if (str[i + 1])
                    printf(" ");
            }
        }
        i++;
    }
    if (n == 0)
        printf("\n");
}
// end ft_echo

// ft_cd
void ft_cd(char *path)
{
    int err;
    char *p;

    err = 0;
    if (!path || ft_strncmp(path, "~", 1) == 0)
    {
        // printf("IN CD\n");
        // p = ft_strjoin(p, getenv("PATH"));
        // printf("PATH = {%s}\n", p);
        err = chdir(getenv("HOME"));
        printf("err = %d\n", err);
        // free(p);
    }
    else
    {
        chdir(path);
    }
    if (err == -1)
        printf("ERROR ASI IN CD\n");
}
// end ft_cd

int ft_pwd(void)
{
    char *buffer;

    buffer = getcwd(NULL, 0);
    if (buffer)
    {
        printf("%s\n", buffer);
        return (1);
    }
    return (0);
}

int ft_count_2d(char **two_dem)
{
    int i;

    i = 0;
    while (two_dem[i])
        i++;
    return (i);
}

t_list_env *ft_lstnew_mod_env(char *content)
{
    t_list_env  *ls;
	int         i;
	char        *key;
	char        *declare;

	i = 0;
	ls = malloc(sizeof(t_list_env));
	declare = "";
	key = NULL;
	if (!ls)
		return (0);
	ls->key = ft_getkey(content);
	ls->value = ft_getvalue_env(content);
	declare = ft_strjoin_bb(declare, ls->key);
	if (ft_detect_equal(ls->key, content) == 0)
		declare = ft_strjoin(declare, "=");
	if (ls->value)
		declare = ft_strjoin(declare, ls->value);
	ls->content = declare;
	ls->next = NULL;
	return (ls);
}

t_list_env *ft_lstlast_env(t_list_env *lst)
{
    if (!lst)
        return (NULL);
    while (lst->next)
        lst = lst->next;
    return (lst);
}

void ft_lstadd_back_env(t_list_env **lst, t_list_env *new)
{
    t_list_env *last;

    if (*lst == NULL)
        *lst = new;
    else
    {
        last = ft_lstlast_env(*lst);
        last->next = new;
    }
}

t_list_env *put_env_to_ls(char **env)
{
    t_list_env *node;
    t_list_env *env_ls;
    int i;

    i = 0;
    env_ls = NULL;
    while (env[i])
    {
        node = ft_lstnew_mod_env(env[i]);
        ft_lstadd_back_env(&env_ls, node);
        i++;
    }
    return (env_ls);
}



char	*ft_getvalue_env(char *content)
{
	int		i;
	int		j;
	char	*value;
    char    *temp;
    
	i = 0;
	j = 0;
	value = "";
	while (content[i])
	{
		if (content[i] == '=' || (content[i] == '+' && content[i + 1] == '='))
		{
			j = i;
			break;
		}
		i++;
	}
	if (j == 0)
		return (content);
	if (j > 0)
    {
        temp = ft_substr(content, j+1, ft_strlen(content));
		value = ft_strjoin_bb(value, temp);
        free(temp);
    }
	return (value);
}


// char    **ft_unset(char **env, char *var_to_unset)
// {
//     int i;
//     int j;
//     int c;
//     int checker;
//     int trigger;
//     int size_var_to_unset;
//     char **new_env;
// 	int ee = 0;

//     new_env = malloc(sizeof(char *) * ft_count_2d(env) + 1);
//     checker = 0;
//     j = 0;
//     i = 0;
//     c = 0;
//     trigger = 0;
//     if (var_to_unset)
//         size_var_to_unset = ft_strlen(var_to_unset);
//     else
//         return (0);
//     while (env[i])
//     {
//         j = 0;
//         size_var_to_unset = ft_strlen(var_to_unset);
// 		if (ee >= 1)
// 			trigger = 0;
//        while (env[i][j])
//        {
//             if(size_var_to_unset == 0 && trigger == 0 && ee == 0)
//             {
//                 trigger = 1;
// 				break;
//             }
//             if (env[i][j] != '=')
//             {
//                 if(env[i][j] == var_to_unset[j])
//                     size_var_to_unset--;
//             }
// 			else
// 				break;
//             j++;
//        }
//         if (trigger == 0)
//         {
//             new_env[c] = ft_substr(env[i], 0, ft_strlen(env[i]));
// 			printf("%s\n", new_env[c]);
//             c++;
//         }
// 		else
// 			ee++;
//        i++;
//     }
//     return (new_env);
// }+

void ft_print_lst_env(t_list_env *ls)
{
    t_list_env *la = ls;
    while (la)
    {
        printf("%s\n", la->content);
        la = la->next;
    }
}

void ft_search_for_var_to_unset(t_list_env **head, char *key)
{
    t_list_env *temp;
    t_list_env *current;
    
    current = *head;
    if (ft_strcmp((*head)->key, key) == 0)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    else
    {
        while (current->next != NULL)
        {
            if (ft_strcmp(current->next->key, key) == 0)
            {
                temp = current->next;
                current->next = current->next->next;
                free(temp);
                break;
            }
            else
                current = current->next;
        }
    }
}


void ft_search_for_var_to_unset_export(t_list_export **head, char *key)
{
    t_list_export *temp;
    t_list_export *current;
    
    current = *head;
    if (ft_strcmp((*head)->key, key) == 0)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    else
    {
        while (current->next != NULL)
        {
            if (ft_strcmp(current->next->key, key) == 0)
            {
                temp = current->next;
                current->next = current->next->next;
                free(temp);
                break;
            }
            else
                current = current->next;
        }
    }
}

void    ft_unset(t_list_env **env, t_list_export **exp, char *var_to_unset)
{
    t_list_env      *env_ls;
    t_list_env      *temp;
    t_list_export   *temp_exp;

    temp = *env;
    temp_exp = *exp;
    if (var_to_unset)
    {
        ft_search_for_var_to_unset(&temp, var_to_unset);
        ft_search_for_var_to_unset_export(&temp_exp, var_to_unset);
    }
}

void ft_env(char **env)
{
    int i;

    i = -1;
    while (++i < ft_count_2d(env))
        printf("%s\n", env[i]);
}

void ft_exit(void)
{
    // smtg to free
    printf("exit\n");
    exit(0);
}

void ft_delete_node_env(t_list_env **head, char *key)
{
	t_list_env *temp;
	t_list_env *current;

	current = *head;
	if (ft_strcmp((*head)->key, key) == 0)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
	else
	{
		while (current->next != NULL)
		{
			if (ft_strcmp(current->next->key, key) == 0)
			{
				temp = current->next;
				current->next = current->next->next;
				free(temp);
				break;
			}
			else
				current = current->next;
		}
	}
}
