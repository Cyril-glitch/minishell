/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:31:28 by mathis            #+#    #+#             */
/*   Updated: 2026/02/13 11:36:38 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	lexer(char *str, t_token_list *token_list)
{
    int i;
    t_token *new_token;
    
    i = 0;
	new_token = ft_db_lstnew();
	token_list->head = new_token;
	token_list->tail = new_token;
	token_list->size = 1;
	init_token(str, token_list->head, &i);
    swipe_space(str, &i);
    while (str[i])
    {
        new_token = ft_db_lstnew();
        ft_db_lstadd_back(token_list, new_token);
        init_token(str, new_token, &i);
        swipe_space(str, &i);
    }
}