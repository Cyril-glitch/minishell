/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtagand <mtagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:04:25 by mtagand           #+#    #+#             */
/*   Updated: 2026/02/17 15:08:22 by mtagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../inc/minishell.h"

int is_build()
{
    return (1);
}

void    init_redir(t_token **current, t_cmd **cmd)
{
    int k;
    t_redir *new_redir;
    
    k = 0;
    new_redir = ft_db_lstnew_redir();
    ft_db_lstadd_back_redir((*cmd)->redirs_list, new_redir);
    new_redir->type = (*current)->type;
    *current = (*current)->next;
    new_redir->file = malloc(sizeof(char) * (ft_strlen((*current)->content) + 1));
    while ((*current)->content[k])
    {
        new_redir->file[k] = (*current)->content[k];
        k++;
    }
    new_redir->file[k] = '\0';
}

void    init_cmd_utils(t_token **current, t_cmd **cmd)
{
    int i;
    int j;

    i = 0;
    while (*current && (*current)->type != PIPE)
    {
        j = 0;
        if (is_redir(*current))
            init_redir(current, cmd);
        else
        {
            (*cmd)->args[i] = malloc(sizeof(char) * (ft_strlen((*current)->content) + 1));
            if (!(*cmd)->args[i])
            {
                //fonction free
            }
            while ((*current)->content[j])
            {
                (*cmd)->args[i][j] = (*current)->content[j];
                j++;
            }
            (*cmd)->args[i][j] = '\0';
            i++;
        }
        if (is_build())
            (*cmd)->is_build = 1;
        *current = (*current)->next;
    }
    (*cmd)->args[i] = NULL;
}

void init_cmd(t_cmd **cmd, t_token **current)
{
    int     i;
    t_token *tmp;
    
    i = 0;
    tmp = *current;
    while (tmp && tmp->type != PIPE)
    {
        if (is_redir(tmp))
        {
            tmp = tmp->next;
            tmp = tmp->next;
        }
        else
        {   
            i++;
            tmp = tmp->next;
        }
    }
    (*cmd)->args = malloc(sizeof(char *) * (i + 1));
    if (!(*cmd)->args)
    {
        //fonction free
        exit(1);
    }
    init_cmd_utils(current, cmd);
}

int    parser(t_token_list *token_list, t_cmd_list *cmd_list)
{
    t_token *current;
    t_cmd *new_cmd;
    
    if (!check_error(token_list))
        return (0);
    current = token_list->head;
    new_cmd = ft_db_lstnew_cmd();
    cmd_list->head = new_cmd;
    cmd_list->tail = new_cmd;
    cmd_list->size = 1;
    init_cmd(&new_cmd, &current);
    while (current)
    {
        if (current->content[0] == '|')
        {
            current = current->next;
            if (!current)
            break;
        }
        new_cmd = ft_db_lstnew_cmd();
        ft_db_lstadd_back_cmd(cmd_list, new_cmd);
        init_cmd(&new_cmd, &current);
    }
    return (1);
}
