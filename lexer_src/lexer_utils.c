/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:41:01 by mathis            #+#    #+#             */
/*   Updated: 2026/02/25 21:07:58 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	swipe_space(char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
}

int	is_separator(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

void	ft_display_list_token(t_token_list *lst)
{
	t_token	*current;

	current = lst->head;
	while (current)
	{
		printf("%s -> ", current->content);
		current = current->next;
	}
	printf("NULL\n");
	current = lst->head;
	while (current)
	{
		printf("%u -> ", current->type);
		current = current->next;
	}
	printf("NULL\n");
	printf("size = %d\n", lst->size);
}
