/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_lst_db_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtagand <mtagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:12:11 by mtagand           #+#    #+#             */
/*   Updated: 2026/02/17 13:14:28 by mtagand          ###   ########.fr       */
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
	if (token->redirs_list)
		ft_db_lstclear_redir(token->redirs_list, del);
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
    t_cmd    *new_cmd;

    new_cmd = malloc(sizeof(t_cmd));
    if (!new_cmd)
		return (NULL);
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	new_cmd->args = NULL;
	new_cmd->redirs_list = NULL;
	new_cmd->fd_in = 0;
	new_cmd->fd_out = 1;
	new_cmd->redirs_list = malloc(sizeof(t_redir_list)); 
    if (new_cmd->redirs_list)
    {
        new_cmd->redirs_list->head = NULL;
        new_cmd->redirs_list->tail = NULL;
        new_cmd->redirs_list->size = 0;
    }
    return (new_cmd);
}
