/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir_lst_db_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 23:46:58 by mathis            #+#    #+#             */
/*   Updated: 2026/02/25 12:16:43 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_db_lstadd_front_redir(t_redir_list *redir_list, t_redir *new)
{
	if (redir_list->head == NULL)
	{
		redir_list->head = new;
		redir_list->tail = new;
	}
	else
	{
		new->next = redir_list->head;
		redir_list->head->prev = new;
		new->prev = NULL;
		redir_list->head = new;
	}
	redir_list->size++;
}

void	ft_db_lstadd_back_redir(t_redir_list *redir_list, t_redir *new)
{
	if (redir_list->head == NULL)
	{
		ft_db_lstadd_front_redir(redir_list, new);
		return ;
	}
	new->prev = redir_list->tail;
	redir_list->tail->next = new;
	new->next = NULL;
	redir_list->tail = new;
	redir_list->size++;
}

void	ft_db_lstdelone_redir(t_redir *token, void (*del)(void*))
{
    if (token->file)
	{
		del(token->file);
	}
	if (token)
	{
		free(token);
	}
}

void	ft_db_lstclear_redir(t_redir_list *redir_list, void (*del)(void*))
{
	t_redir	*current;
	t_redir	*tmp;

	current = redir_list->head;
	tmp = current;
	while (current)
	{
		if (!current->next)
		{
			ft_db_lstdelone_redir(tmp, del);
			break;
		}
		current = current->next;
		ft_db_lstdelone_redir(tmp, del);
		tmp = current;
	}
	redir_list->head = NULL;
	redir_list->tail = NULL;
	redir_list->size = 0;
	free(redir_list);
	redir_list = NULL;
}

t_redir    *ft_db_lstnew_redir()
{
    t_redir    *new;

    new = malloc(sizeof(t_redir));
    if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->file = NULL;
    return (new);
}