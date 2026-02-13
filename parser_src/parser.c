/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtagand <mtagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:04:25 by mtagand           #+#    #+#             */
/*   Updated: 2026/02/13 18:58:14 by mtagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../inc/minishell.h"

void init_cmd(t_token_list *token_list, t_cmd *cmd, int *i)
{
    t_token *current;
    int     j;
    
    cmd->fd_in = 0;
    cmd->fd_out = 1;
    current = token_list->head;
    j = 0;
    
    dprintf(2, "%u", current->type);
    while (current && current->type != PIPE)
    {
        j++;
        current = current->next;
    }
    cmd->args = malloc(sizeof(char *) * (j + 1));
    current = token_list->head;
    while (current && current->type != PIPE)
    {
        j = 0;
        cmd->args[*i] = malloc(sizeof(char) * (ft_strlen(current->content) + 1));
        while (current->content[j])
        {
            cmd->args[*i][j] = current->content[j];
            j++;
        }
        cmd->args[*i][j] = '\0';
        (*i)++;
        current = current->next;
    }
}

void    parser(t_token_list *token_list, t_cmd_list *cmd_list)
{
    int i;
    t_cmd *new_cmd;
    
    i = 0;
    new_cmd = ft_db_lstnew_cmd();
    cmd_list->head = new_cmd;
    cmd_list->tail = new_cmd;
    cmd_list->size = 1;
    init_cmd(token_list, cmd_list->head, &i);
    ft_display_list_cmd(cmd_list);
}