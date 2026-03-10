/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:46:59 by mathis            #+#    #+#             */
/*   Updated: 2026/03/10 12:41:58 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_msg_error(char *msg)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("'\n", 2);
}

int	check_error_pipe(t_token *current)
{
	if ((current->type == 1) && (!current->prev || !current->next))
		return (print_msg_error("|"), 0);
	if ((current->type == 1) && current->next)
	{
		if (current->next->type == 1)
			return (print_msg_error("|"), 0);
	}
	if ((current->type == 6) && (!current->prev || !current->next))
		return (print_msg_error("||"), 0);
	if ((current->type == 6) && current->next)
	{
		if (current->next->type == 1)
			return (print_msg_error("||"), 0);
	}
	return (1);
}

int	print_and_return(t_token *current)
{
	if (current->next->type == 1)
		return (print_msg_error("|"), 0);
	if (current->next->type == 2)
		return (print_msg_error("<"), 0);
	if (current->next->type == 3)
		return (print_msg_error(">"), 0);
	if (current->next->type == 4)
		return (print_msg_error("<<"), 0);
	if (current->next->type == 5)
		return (print_msg_error(">>"), 0);
	if (current->next->type == 6)
		return (print_msg_error("||"), 0);
	return (1);
}

int	check_error_redir(t_token *current)
{
	int	i;

	i = 0;
	if (is_redir(current) && current->next && !print_and_return(current))
		return (0);
	if (is_redir(current))
	{
		while (current->content[i])
			i++;
		if (is_redir(current) && !current->next && i <= 2)
			return (print_msg_error("newline"), 0);
		if (i > 2 && current->content[0] == '>')
			return (print_msg_error(">"), 0);
		if (i > 2 && current->content[0] == '<')
			return (print_msg_error("<"), 0);
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
        {
            g_sig_status = 2;
			return (0);
        }
		if (!check_error_redir(current))
        {
            g_sig_status = 2;
			return (0);
        }
		current = current->next;
	}
	return (1);
}
