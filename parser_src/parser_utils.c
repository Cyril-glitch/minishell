/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtagand <mtagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 18:33:55 by mtagand           #+#    #+#             */
/*   Updated: 2026/02/13 18:48:52 by mtagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_display_list_cmd(t_cmd_list *lst)
{
	t_cmd	*current;
    int i;

    i = 0;
	current = lst->head;
	while (current)
	{
		printf("%s -> ", current->args[i]);
        i++;
		current = current->next;
	}
	printf("NULL\n");
	printf("size = %d\n", lst->size);
}