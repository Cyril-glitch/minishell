/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 18:33:55 by mtagand           #+#    #+#             */
/*   Updated: 2026/02/15 20:46:08 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_display_list_cmd(t_cmd_list *lst)
{
	t_cmd	*current;
    int i;

	current = lst->head;
	while (current)
	{
		i = 0;
		while (current->args[i])
		{
			printf("%s -> ", current->args[i]);
			i++;
		}
		printf("NULL\n");
		current = current->next;
	}
	printf("size = %d\n", lst->size);
}

int is_redir(t_token *current)
{
    if (current->type >= 2 && current->type <= 5)
        return (1);
    return (0);
}