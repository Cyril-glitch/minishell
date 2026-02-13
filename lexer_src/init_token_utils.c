/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtagand <mtagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:42:45 by mathis            #+#    #+#             */
/*   Updated: 2026/02/13 12:32:03 by mtagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_db_lstadd_front(t_token_list *token_list, t_token *new)
{
	if (token_list->head == NULL)
	{
		token_list->head = new;
		token_list->tail = new;
	}
	else
	{
		new->next = token_list->head;
		token_list->head->prev = new;
		new->prev = NULL;
		token_list->head = new;
	}
	token_list->size++;
}

void	ft_db_lstadd_back(t_token_list *token_list, t_token *new)
{
	if (token_list->head == NULL)
	{
		ft_db_lstadd_front(token_list, new);
		return ;
	}
	new->prev = token_list->tail;
	token_list->tail->next = new;
	new->next = NULL;
	token_list->tail = new;
	token_list->size++;
}

void	ft_db_lstdelone(t_token *token, void (*del)(void*))
{
	del(token->content);
	free(token);
}

void	ft_db_lstclear(t_token_list *token_list, void (*del)(void*))
{
	t_token	*current;
	t_token	*tmp;

	current = token_list->head;
	tmp = current;
	while (current)
	{
		current = current->next;
		ft_db_lstdelone(tmp, del);
		tmp = current;
	}
	token_list->head = NULL;
	token_list->tail = NULL;
	token_list->size = 0;
}

t_token    *ft_db_lstnew()
{
    t_token    *new;

    new = malloc(sizeof(t_token));
    if (!new)
        return (NULL);
    new->next = NULL;
    new->prev = NULL;
    return (new);
}