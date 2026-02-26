/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:04:25 by mtagand           #+#    #+#             */
/*   Updated: 2026/02/26 08:42:35 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_redir(t_token **current, t_cmd **cmd, t_data *data)
{
	int		k;
	t_redir	*new_redir;

	k = 0;
	new_redir = ft_db_lstnew_redir();
	if (!new_redir)
		ft_shell_exit(data);
	ft_db_lstadd_back_redir((*cmd)->redirs_list, new_redir);
	new_redir->type = (*current)->type;
	*current = (*current)->next;
	new_redir->file = malloc(sizeof(char) * (ft_strlen((*current)->content)
				+ 1));
	if (!new_redir->file)
		ft_shell_exit(data);
	while ((*current)->content[k])
	{
		new_redir->file[k] = (*current)->content[k];
		k++;
	}
	new_redir->file[k] = '\0';
}

void	init_cmd_utils(t_token **current, t_cmd **cmd, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (*current && (*current)->type != PIPE)
	{
		j = 0;
		if (is_redir(*current))
			init_redir(current, cmd, data);
		else
		{
			(*cmd)->args[i] = malloc((ft_strlen((*current)->content) + 1));
			if (!(*cmd)->args[i])
				ft_shell_exit(data);
			while ((*current)->content[j])
			{
				(*cmd)->args[i][j] = (*current)->content[j];
				j++;
			}
			(*cmd)->args[i][j] = '\0';
			i++;
		}
		*current = (*current)->next;
	}
	(*cmd)->args[i] = NULL;
}

void	init_cmd(t_cmd **cmd, t_token **current, t_data *data)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = *current;
	while (tmp && tmp->type != PIPE)
	{
		if (is_redir(tmp))
		{
			tmp = tmp->next;
			tmp = tmp->next;
		}
		else
		{
			i++;
			tmp = tmp->next;
		}
	}
	(*cmd)->args = malloc(sizeof(char *) * (i + 1));
	if (!(*cmd)->args)
		ft_shell_exit(data);
	init_cmd_utils(current, cmd, data);
	(*cmd)->is_build = is_build(cmd);
}

t_cmd	*init_head_cmd(t_data *data)
{
	t_cmd	*new_cmd;

	new_cmd = ft_db_lstnew_cmd();
	if (!new_cmd)
		ft_shell_exit(data);
	data->cmd_list->head = new_cmd;
	data->cmd_list->tail = new_cmd;
	data->cmd_list->size = 1;
	return (new_cmd);
}

int	parser(t_data *data)
{
	t_token	*current;
	t_cmd	*new_cmd;

	if (!check_error(data->token_list))
		return (0);
	current = data->token_list->head;
	new_cmd = init_head_cmd(data);
	init_cmd(&new_cmd, &current, data);
	while (current)
	{
		if (current->content[0] == '|')
		{
			current = current->next;
			if (!current)
				break ;
		}
		new_cmd = ft_db_lstnew_cmd();
		if (!new_cmd)
			ft_shell_exit(data);
		ft_db_lstadd_back_cmd(data->cmd_list, new_cmd);
		init_cmd(&new_cmd, &current, data);
	}
	return (1);
}
