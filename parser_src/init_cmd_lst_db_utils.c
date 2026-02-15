/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_lst_db_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:12:11 by mtagand           #+#    #+#             */
/*   Updated: 2026/02/15 21:13:50 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_db_lstadd_front_cmd(t_cmd_list *cmd_list, t_cmd *new)
{
	if (cmd_list->head == NULL)
	{
		cmd_list->head = new;
		cmd_list->tail = new;
	}
	else
	{
		new->next = cmd_list->head;
		cmd_list->head->prev = new;
		new->prev = NULL;
		cmd_list->head = new;
	}
	cmd_list->size++;
}

void	ft_db_lstadd_back_cmd(t_cmd_list *cmd_list, t_cmd *new)
{
	if (cmd_list->head == NULL)
	{
		ft_db_lstadd_front_cmd(cmd_list, new);
		return ;
	}
	new->prev = cmd_list->tail;
	cmd_list->tail->next = new;
	new->next = NULL;
	cmd_list->tail = new;
	cmd_list->size++;
}

void	ft_db_lstdelone_cmd(t_cmd *token, void (*del)(void*))
{
    int i;

    i = 0;
    while (token->args[i])
    {
    	del(token->args[i]);
        i++;
    }
	if (token->args)
		free(token->args);
	if (token)
    	free(token);
}

void	ft_db_lstclear_cmd(t_cmd_list *cmd_list, void (*del)(void*))
{
	t_cmd	*current;
	t_cmd	*tmp;

	current = cmd_list->head;
	tmp = current;
	while (current)
	{
		current = current->next;
		ft_db_lstdelone_cmd(tmp, del);
		tmp = current;
	}
	cmd_list->head = NULL;
	cmd_list->tail = NULL;
	cmd_list->size = 0;
}

t_cmd    *ft_db_lstnew_cmd()
{
    t_cmd    *new;

    new = malloc(sizeof(t_cmd));
    if (!new)
        return (NULL);
    new->next = NULL;
    new->prev = NULL;
	new->args = NULL;
	new->fd_in = 0;
	new->fd_out = 1;
    return (new);
}