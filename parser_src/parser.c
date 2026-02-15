/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:04:25 by mtagand           #+#    #+#             */
/*   Updated: 2026/02/15 21:15:55 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../inc/minishell.h"

void    init_cmd_utils(t_token **current, t_cmd *cmd)
{
    int j;
    int i;

    i = 0;
    while (*current && (*current)->type != PIPE)
    {
        j = 0;
        cmd->args[i] = malloc(sizeof(char) * (ft_strlen((*current)->content) + 1));
        if (!cmd->args[i])
        {
            //fonction free
            exit(1);
        }
        while ((*current)->content[j])
        {
            cmd->args[i][j] = (*current)->content[j];
            j++;
        }
        cmd->args[i][j] = '\0';
        i++;
        *current = (*current)->next;
    }
    cmd->args[i] = NULL;
}

void init_cmd(t_cmd *cmd, t_token **current)
{
    int     i;
    t_token *tmp;
    
    i = 0;
    tmp = *current;
    while (tmp && tmp->type != PIPE)
    {
        i++;
        tmp = tmp->next;
    }
    cmd->args = malloc(sizeof(char *) * (i + 1));
    if (!cmd->args)
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
    init_cmd(new_cmd, &current);
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
        init_cmd(new_cmd, &current);
    }
    return (1);
    //ft_display_list_cmd(cmd_list);
}