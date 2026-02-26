/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:46:59 by mathis            #+#    #+#             */
/*   Updated: 2026/02/25 22:07:05 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_error_pipe(t_token *current)
{
	if ((current->type == 1) && (!current->prev || !current->next))
		return (ft_putstr_fd("minishell: syntax error near unexpected token \
			`|'\n",
				2), 0);
	if ((current->type == 1) && current->next)
	{
		if (current->next->type == 1)
			return (ft_putstr_fd("minishell: syntax error near unexpected \
				token `|'\n",
					2), 0);
	}
	if ((current->type == 6) && (!current->prev || !current->next))
		return (ft_putstr_fd("minishell: syntax error near unexpected token \
			`||'\n",
				2), 0);
	if ((current->type == 6) && current->next)
	{
		if (current->next->type == 1)
			return (ft_putstr_fd("minishell: syntax error near unexpected \
				token `||'\n",
					2), 0);
	}
	return (1);
}

int	print_and_return(t_token *current)
{
	if (current->next->type == 1)
		return (ft_putstr_fd("minishell: syntax error near unexpected \
			token `|'\n", 2), 0);
	if (current->next->type == 2)
		return (ft_putstr_fd("minishell: syntax error near unexpected \
			token `<'\n", 2), 0);
	if (current->next->type == 3)
		return (ft_putstr_fd("minishell: syntax error near unexpected \
			token `>'\n", 2), 0);
	if (current->next->type == 4)
		return (ft_putstr_fd("minishell: syntax error near unexpected \
			token `<<'\n", 2), 0);
	if (current->next->type == 5)
		return (ft_putstr_fd("minishell: syntax error near unexpected \
			token `>>'\n", 2), 0);
	if (current->next->type == 6)
		return (ft_putstr_fd("minishell: syntax error near unexpected \
			token `||'\n", 2), 0);
	return (1);
}

int	check_error_redir(t_token *current)
{
	int	i;

	i = 0;
	if (is_redir(current) && !current->next)
		return (ft_putstr_fd("minishell: syntax error near unexpected token\
			 `newline'\n", 2), 0);
	if (is_redir(current) && current->next && !print_and_return(current))
		return (0);
	if (is_redir(current))
	{
		while (current->content[i])
			i++;
		if (i > 2 && current->content[0] == '<')
			return (ft_putstr_fd("minishell: syntax error near unexpected \
				token `<'\n", 2), 0);
		if (i > 2 && current->content[0] == '>')
			return (ft_putstr_fd("minishell: syntax error near unexpected \
				token `>'\n", 2), 0);
	}
	return (1);
}

int	check_error(t_token_list *token_list)
{
	t_token	*current;

	current = token_list->head;
	while (current)
	{
		if (!check_error_pipe(current))
			return (0);
		if (!check_error_redir(current))
			return (0);
		current = current->next;
	}
	return (1);
}
