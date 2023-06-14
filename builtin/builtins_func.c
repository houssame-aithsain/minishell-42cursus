/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gothmane <gothmane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 22:09:30 by gothmane          #+#    #+#             */
/*   Updated: 2023/06/12 15:16:06 by gothmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_second_delete_func_part(t_list_env **curr, char *key)
{
    t_list_env *current = *curr;
    t_list_env *temp = *curr;
    while (current->next != NULL)
    {
        if (ft_strcmp(current->next->key, key) == 0)
        {
            temp = current->next;
            current->next = current->next->next;
            free(temp->content);
            free(temp->key);
            free(temp);
            break;
        }
        else
            current = current->next;
    }
}

void ft_wrapped_free_for_delete(t_list_export *temp)
{
    if (temp->key)
        free(temp->key);
    if (temp->value)
        free(temp->value);
    if (temp->content)
        free(temp->content);
    if (temp)
        free(temp);
}

int ft_check_minus_n_(char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (!str)
        return (0);
    while (str[i])
    {
        if (i == 0 && str[i] == '-')
            j++;
        if (str[i] == 'n')
            j++;
        i++;
    }
    if (i == j && i != 0)
        return (1);
    return (0);
}

void ft_print_minus_n_after(char **str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (ft_check_minus_n_(str[i]) == 1)
        {
            printf("%s", str[i]);
            if (str[i + 1])
                printf(" ");
        }
        i++;
    }
}
// ft_echo
void    ft_printing_echo_content(char **str, int *i, int c)
{
    printf("%s", str[*i]);
    if (str[*i + 1])
    {
        printf(" ");
        if (c == 1)
            ft_print_minus_n_after(&str[*i]);
    }
    (*i)++;
}
void    ft_echo(char **str)
{
    int i;
    int c;
    int k;

    c = 0;
    i = 0;
    k = 0;
    while (str[i])
    {
        k = ft_check_minus_n_(str[i]);
        if (i == 0 && k == 1)
        {
            c = 1;
            i++;
        }
        else if (i > 0 && k == 1 && c == 1)
            i++;
        else if (i != 0 || k == 0)
            ft_printing_echo_content(str, &i, c);
        else
            i++;
    }
    if (c == 0)
        printf("\n");
    ft_free_args(str);
}
// end ft_echo

int ft_find_key__v2(t_list_env *env)
{
    while (env)
    {
        if (ft_strcmp(env->key, "HOME") == 0)
            return (1);
        env = env->next;
    }
    return (0);
}

char *ft_getval_env(char *key, t_list_env *env_ls)
{
    t_list_env *env;

    env = env_ls;
    while (env)
    {
        if (ft_strcmp(key, env->key) == 0)
            return (env->value);
        // printf("key = %s\n", env->key);
        env = env->next;
    }
    return (NULL);
}

void ft_wrapped_free_for_delete_env(t_list_env *temp)
{
    if (temp->key)
        free(temp->key);
    if (temp->value)
        free(temp->value);
    if (temp->content)
        free(temp->content);
    if (temp)
        free(temp);
}

void ft_delete_node_env_for_cd(t_list_env **head, char *key)
{
    t_list_env *temp;
    t_list_env *current;

    current = *head;
    if (ft_strcmp((*head)->key, key) == 0)
    {
        temp = *head;
        *head = (*head)->next;
        ft_wrapped_free_for_delete_env(temp);
    }
    else
    {
        while (current->next != NULL)
        {
            if (ft_strcmp(current->next->key, key) == 0)
            {
                temp = current->next;
                current->next = current->next->next;
                ft_wrapped_free_for_delete_env(temp);
                break;
            }
            else
                current = current->next;
        }
    }
}

void ft_replace_pwd(t_list_env **env_ls)
{
    char *oldpwd;
    char *pwd;
    char *buffer;
    char *value;

    value = ft_getval_env("PWD", *env_ls);
    if (!value)
        return;
    buffer = getcwd(NULL, 0);
    oldpwd = ft_strdup("OLDPWD=");
    oldpwd = ft_strjoin(oldpwd, value);
    ft_delete_node_env_for_cd(env_ls, "OLDPWD");
    ft_lstadd_back_env(env_ls, ft_lstnew_mod_env(oldpwd));
    ft_delete_node_env(env_ls, "PWD");
    pwd = ft_strdup("PWD=");
    if (buffer)
        pwd = ft_strjoin(pwd, buffer);
    ft_lstadd_back_env(env_ls, ft_lstnew_mod_env(pwd));
    free(oldpwd);
    free(buffer);
    free(value);
    free(pwd);
}

// ft_cd
void ft_cd(char *path, t_list_env **env_ls)
{
    int err;
    char *p;

    err = 0;
    if (!path || ft_strncmp(path, "~", 1) == 0)
        err = chdir(getenv("HOME"));
    else
    {
        err = chdir(path);
        ft_replace_pwd(env_ls);
    }
    if (err == -1)
    {
        printf("minishell: No such file or directory\n");
        if (ft_find_key__v2(*env_ls) == 1)
            exit_status = 0;
        else
            exit_status = 1;
    }
}
// end ft_cd

int ft_pwd(void)
{
    char *buffer;

    buffer = getcwd(NULL, 0);
    if (buffer)
    {
        printf("%s\n", buffer);
        free(buffer);
        return (1);
    }
    free(buffer);
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
    t_list_env *ls;
    int i;
    char *key;
    char *declare;

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
    node = ft_lstnew_mod_env("x");
    ft_lstadd_back_env(&env_ls, node);
    while (env[i])
    {
        node = ft_lstnew_mod_env(env[i]);
        ft_lstadd_back_env(&env_ls, node);
        i++;
    }
    return (env_ls);
}

char *ft_getvalue_env(char *content)
{
    int i;
    int j;
    char *value;
    char *temp;

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
        temp = ft_substr(content, j + 1, ft_strlen(content));
        value = ft_strjoin_bb(value, temp);
        free(temp);
    }
    return (value);
}

void ft_print_lst_env(t_list_env *ls)
{
    t_list_env *la = ls;

    if (!la)
        return;
    while (la)
    {
        if (ft_strcmp(la->content, "xx") != 0)
            printf("%s\n", la->content);
        la = la->next;
    }
}

void ft_search_for_var_to_unset(t_list_env **head, char *key)
{
    t_list_env *temp;
    t_list_env *current;

    current = *head;
    if (current && ft_strcmp((*head)->key, key) == 0)
    {
        temp = *head;
        *head = (*head)->next;
        if (temp->key)
            free(temp->key);
        if (temp->content)
            free(temp->content);
        if (temp)
            free(temp);
    }
    else
        ft_second_delete_func_part(head, key);
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
        ft_wrapped_free_for_delete(temp);
    }
    else
    {
        while (current->next != NULL)
        {
            if (ft_strcmp(current->next->key, key) == 0)
            {
                temp = current->next;
                current->next = current->next->next;
                ft_wrapped_free_for_delete(temp);
                break;
            }
            else
                current = current->next;
        }
    }
}

void ft_unset(t_list_env **env, t_list_export **exp, char **var_to_unset)
{
    t_list_env *env_ls;
    t_list_env *temp;
    t_list_export *temp_exp;
    int i;

    i = 0;
    temp = *env;
    temp_exp = *exp;
    while (var_to_unset[i])
    {
        ft_search_for_var_to_unset_export(&temp_exp, var_to_unset[i]);
        ft_search_for_var_to_unset(&temp, var_to_unset[i]);
        i++;
    }
}

void ft_env(char **env)
{
    int i;

    i = -1;
    while (++i < ft_count_2d(env))
        printf("%s\n", env[i]);
}

int _ft_exit_v(t_bash *ptr, int size_c)
{
    int j = 0;

    while (ptr->arg[0][j])
    {
        if (ft_isalpha(ptr->arg[0][j]) == 1)
        {
            printf("minishell: exit: %s: numeric argument required\n", ptr->arg[0]);
            exit(255);
        }
        if (size_c > 1)
        {
            printf("minishell: exit: too many arguments\n");
            exit_status = 1;
            return (1);
        }
        j++;
    }
    return (0);
}

int _ft_exit_check_arg(t_bash *ptr)
{
    int j = 0;
    int i = 0;
    while (ptr->arg[i])
    {
        j = 0;
        while (ptr->arg[i][j])
        {
            if (ft_isalpha(ptr->arg[i][j]) == 1)
            {
                printf("minishell: exit: %s: numeric argument required\n", ptr->arg[i]);
                exit(255);
            }
            j++;
        }
        i++;
    }
    return (0);
}

void ft_exit(t_bash *ptr)
{
    int a;
    int size_c;

    a = -404;
    size_c = 0;
    if (ptr->arg)
        size_c = ft_count_2d(ptr->arg);
    if (!ptr)
        return;
    if (size_c == 0)
        exit(exit_status);
    if (_ft_exit_v(ptr, size_c) == 1)
        return;
    _ft_exit_check_arg(ptr);
    if (ptr->arg[0])
        a = ft_atoi(ptr->arg[0]);
    else
        exit(exit_status);
    if (a != -404)
        exit(a);
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
        free(temp->content);
        free(temp->key);
        free(temp);
    }
    else
        ft_second_delete_func_part(head, key);
}
