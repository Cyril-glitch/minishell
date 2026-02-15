/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:46:59 by mathis            #+#    #+#             */
/*   Updated: 2026/02/15 20:48:00 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../inc/minishell.h"

int check_error_pipe(t_token *current)
{
    if (current->type == 1 && (!current->prev || !current->next))
        return (0);
    if (current->type == 1 && current->next)
    {
        if (current->next->type == 1)
            return (0);
    }
    return (1);
}

int check_error_redir(t_token *current)
{
    int i;

    i = 0;
    if (is_redir(current) && !current->next)
        return (0);
    if (is_redir(current) && current->next)
    {
        if (is_redir(current->next) || current->next->type == 1)
            return (0);
    }
    if (is_redir(current))
    {
        while (current->content[i])
            i++;
        if (i > 2)
            return (0);
    }
    return (1);
}

int check_error(t_token_list *token_list)
{
    t_token *current;

    current = token_list->head;
    while (current)
    {
        if (!check_error_pipe(current))
        {
            //fonction free
            return (printf("error pipe\n"), 0);
        }
        if (!check_error_redir(current))
        {
            //fonction free
            return (printf("error redir\n"), 0); 
        }
        current = current->next;
    }
    return (1);
}