/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtagand <mtagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:31:28 by mathis            #+#    #+#             */
/*   Updated: 2026/02/13 15:57:17 by mtagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int     verif_quote(char *str)
{
    int i;
    char quote;

    i = 0;
    quote = 'q';
    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '"')
        {
            quote = str[i];
            i++;
            while (str[i] != quote)
            {
                if (!str[i])
                {
                    return (0);
                }
                i++;
            }
        }
        i++;
    }
    return (1);
}

void	lexer(char *str, t_token_list *token_list)
{
    int i;
    t_token *new_token;
    
    if (!verif_quote(str))
    {
        printf(">\n");
        return;
    }
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
    ft_display_list(token_list);
    ft_db_lstclear(token_list, free);
    free(str);
}
