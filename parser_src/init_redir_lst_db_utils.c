/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redir_lst_db_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 23:46:58 by mathis            #+#    #+#             */
/*   Updated: 2026/02/15 23:54:51 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_db_lstadd_front_redir(t_redir *redir, t_redir *new)
{
	if (redir == NULL)
		redir = new;
	else
	{
		new->next = redir;
		redir->prev = new;
		new->prev = NULL;
		redir = new;
	}
}

void	ft_db_lstadd_back_cmd(t_redir *redir, t_redir *new)
{
	if (redir == NULL)
	{
		ft_db_lstadd_front_redir(redir, new);
		return ;
	}
	new->prev = redir;
	redir->next = new;
	new->next = NULL;
	redir = new;
}

void	ft_db_lstdelone_redir(t_redir *token, void (*del)(void*))
{
    int i;

    i = 0;
    while (token->file[i])
    {
    	del(token->file[i]);
        i++;
    }
	if (token->file)
		free(token->file);
	if (token)
    	free(token);
}

void	ft_db_lstclear_redir(t_redir *redir, void (*del)(void*))
{
	t_redir	*current;
	t_redir	*tmp;

	current = redir;
	tmp = current;
	while (current)
	{
		current = current->next;
		ft_db_lstdelone_redir(tmp, del);
		tmp = current;
	}
	redir = NULL;
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
}