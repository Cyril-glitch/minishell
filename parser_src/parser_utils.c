/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtagand <mtagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 18:33:55 by mtagand           #+#    #+#             */
/*   Updated: 2026/02/16 15:52:22 by mtagand          ###   ########.fr       */
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
void	ft_display_list_redir(t_redir_list *lst)
{
	t_redir	*current;
    int i;

	current = lst->head;
	while (current)
	{
		i = 0;
		while (current->file)
		{
			printf("%s -> ", current->file);
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