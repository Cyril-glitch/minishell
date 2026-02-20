/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:31:28 by mathis            #+#    #+#             */
/*   Updated: 2026/02/20 11:14:02 by mathis           ###   ########.fr       */
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

int     lexer(t_data *data)
{
    int i;
    t_token *new_token;
    
    if (!verif_quote(data->line))
    {
        printf(">\n");
        return (0);
    }
    i = 0;
	new_token = ft_db_lstnew_token(data);
    if (!new_token)
        ft_shell_exit(data);
	data->token_list->head = new_token;
	data->token_list->tail = new_token;
	data->token_list->size = 1;
	init_token(data, data->token_list->head, &i);
    swipe_space(data->line, &i);
    while (data->line[i])
    {
        new_token = ft_db_lstnew_token();
        ft_db_lstadd_back_token(data->token_list, new_token);
        init_token(data, new_token, &i);
        swipe_space(data->line, &i);
    }
    return (1);
}
