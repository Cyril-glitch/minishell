/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:28:39 by cycolonn          #+#    #+#             */
/*   Updated: 2026/03/10 15:50:19 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env_list	*ft_lstlast_env(t_env_list *lst)
{
	t_env_list	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current->next)
	{
		current = current->next;
	}
	return (current);
}

void	ft_lstadd_back_env(t_env_list **lst, t_env_list *new)
{
	t_env_list	*last;

	if (*lst)
	{
		last = ft_lstlast_env(*lst);
		last->next = new;
		new->prev = last;
	}
	else
		*lst = new;
}

void	ft_clear_node_env(t_env_list *node)
{
	if (!node)
		return ;
	if (node->line)
		free(node->line);
	if (node->key)
		free(node->key);
	if (node->content)
		free(node->content);
	if (node)
		free(node);
}

void	ft_lstclear_env(t_env_list **lst)
{
	t_env_list	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_clear_node_env(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
