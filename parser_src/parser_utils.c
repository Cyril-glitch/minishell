/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtagand <mtagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 18:33:55 by mtagand           #+#    #+#             */
/*   Updated: 2026/02/27 10:35:05 by mtagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_build(t_cmd **cmd)
{
	if (!((*cmd)->args[0]) || !ft_strlen(((*cmd)->args[0])))
		return ((*cmd)->build = DFL, -1);
	if (!ft_strcmp((*cmd)->args[0], "echo"))
		return ((*cmd)->build = ECHOO, 1);
	if (!ft_strcmp((*cmd)->args[0], "cd"))
		return ((*cmd)->build = CD, 1);
	if (!ft_strcmp((*cmd)->args[0], "pwd"))
		return ((*cmd)->build = PWD, 1);
	if (!ft_strcmp((*cmd)->args[0], "export"))
		return ((*cmd)->build = EXPORT, 1);
	if (!ft_strcmp((*cmd)->args[0], "unset"))
		return ((*cmd)->build = UNSET, 1);
	if (!ft_strcmp((*cmd)->args[0], "env"))
		return ((*cmd)->build = ENV, 1);
	if (!ft_strcmp((*cmd)->args[0], "exit"))
		return ((*cmd)->build = EXIT, 1); 
	return ((*cmd)->build = DFL, 0);
}

void	ft_display_list_cmd(t_cmd_list *lst)
{
	t_cmd	*current;
	int		i;

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
		if (current->redirs_list)
			ft_display_list_redir(current->redirs_list);
		printf("is_build = %d\n", current->is_build);
		current = current->next;
	}
	printf("size = %d\n", lst->size);
}

void	ft_display_list_redir(t_redir_list *lst)
{
	t_redir	*current;

	current = lst->head;
	while (current)
	{
		printf("%s -> ", current->file);
		current = current->next;
	}
	printf("NULL\n");
	printf("size = %d\n", lst->size);
}

int	is_redir(t_token *current)
{
	if (current->type >= 2 && current->type <= 5)
		return (1);
	return (0);
}
