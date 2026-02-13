/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:33:25 by mathis            #+#    #+#             */
/*   Updated: 2026/02/13 11:34:20 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_word(char *str, t_token *token, int *i)
{
    int j;
    int k;
    
    j = 0;
    k = 0;
	while (!is_separator(str[*i + j]) && str[*i + j])
        j++;
	token->content = malloc(sizeof(char) * (j + 1));
	if (!token->content)
		return;
	j = 0;
    k = 0;
	while (!is_separator(str[*i + j - k]) && str[*i + j - k])
	{
        token->content[j] = str[*i];
		(*i)++;
		j++;
        k++;
	}
	token->content[*i] = '\0';
	token->type = WORD;
}

void    init_pipe(char *str, t_token *token, int *i)
{
    token->content = malloc(sizeof(char) * 2);
    if (!token->content)
        return;
    token->content[0] = '|';
    token->content[1] = '\0';
    (*i)++;
    token->type = PIPE;
}

void	init_redir_in(char *str, t_token *token, int *i)
{
    int j;
    
    j = 0;
	while (str[*i + j] == '<')
        j++;
	token->content = malloc(sizeof(char) * (j + 1));
    if (!token->content)
        return;
	j = 0;
	while (str[*i] == '<')
	{
        token->content[j] = str[*i];
		(*i)++;
		j++;
	}
	token->content[*i] = '\0';
	if (j == 1)
        token->type = REDIR_IN;
    if (j == 2)
        token->type = D_REDIR_IN;
}

void	init_redir_out(char *str, t_token *token, int *i)
{
    int j;
    
    j = 0;
	while (str[*i + j] == '>')
        j++;
	token->content = malloc(sizeof(char) * (j + 1));
	if (!token->content)
        return;
    j = 0;
	while (str[*i] == '>')
	{
        token->content[j] = str[*i];
		(*i)++;
		j++;
	}
	token->content[*i] = '\0';
	if (j == 1)
        token->type = REDIR_OUT;
    if (j == 2)
        token->type = D_REDIR_OUT;
}

void	init_token(char *str, t_token *token, int *i)
{
    swipe_space(str, i);
	if (!is_separator(str[*i]))
    {
        init_word(str, token, i);
        return;
    }
	if (str[*i] == '|')
    {
        init_pipe(str, token, i);
        return;
    }
    if (str[*i] == '<')
    {
        init_redir_in(str, token, i);
        return;
    }
    if (str[*i] == '>')
    {
        init_redir_out(str, token, i);
        return;
    }
}