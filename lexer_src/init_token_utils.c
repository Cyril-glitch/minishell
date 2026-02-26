/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 16:13:52 by mtagand           #+#    #+#             */
/*   Updated: 2026/02/25 21:53:21 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	nb_of_malloc(char *str, int *i, int *j, char quote)
{
	while (!is_separator(str[*i + *j]) && str[*i + *j])
	{
		if (str[*i + *j] == '\'' || str[*i + *j] == '"')
		{
			quote = str[*i + *j];
			(*j)++;
			while (str[*i + *j] != quote)
				(*j)++;
		}
		(*j)++;
	}
}

void	copy_word(char *str, int *i, char quote, t_token *token)
{
	int	j;

	j = 0;
	while (!is_separator(str[*i]) && str[*i])
	{
		if (str[*i] == '\'' || str[*i] == '"')
		{
			quote = str[*i];
			token->content[j] = str[*i];
			(*i)++;
			j++;
			while (str[*i] != quote)
			{
				token->content[j] = str[*i];
				(*i)++;
				j++;
			}
		}
		token->content[j] = str[*i];
		(*i)++;
		j++;
	}
}
