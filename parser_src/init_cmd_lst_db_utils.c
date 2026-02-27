/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_lst_db_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtagand <mtagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:12:11 by mtagand           #+#    #+#             */
/*   Updated: 2026/02/27 12:57:42 by mtagand          ###   ########.fr       */
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

void	ft_db_lstdelone_cmd(t_cmd *cmd, void (*del)(void *))
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		del(cmd->args[i]);
		i++;
	}
	if (cmd->way)
		free(cmd->way);
	if (cmd->redirs_list)
		ft_db_lstclear_redir(cmd->redirs_list, del);
	if (cmd->args)
		free(cmd->args);
	if (cmd)
		free(cmd);
}

void	ft_db_lstclear_cmd(t_cmd_list *cmd_list, void (*del)(void *))
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

t_cmd	*ft_db_lstnew_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	new_cmd->args = NULL;
	new_cmd->way = NULL;
	new_cmd->redirs_list = NULL;
	new_cmd->is_build = 0;
	new_cmd->redirs_list = malloc(sizeof(t_redir_list));
	if (!new_cmd->redirs_list)
		return (NULL);
	new_cmd->redirs_list->head = NULL;
	new_cmd->redirs_list->tail = NULL;
	new_cmd->redirs_list->size = 0;
	return (new_cmd);
}
