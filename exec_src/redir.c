/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtagand <mtagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:26:44 by mathis            #+#    #+#             */
/*   Updated: 2026/03/02 13:52:56 by mtagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	open_file(t_redir *current, int *fd, int *flag)
{
	if (current->type == REDIR_IN)
	{
		*fd = open(current->file, O_RDONLY);
		if (*fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(current->file, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		// else if (!cmd->way)
		// {
		// 	ft_putstr_fd("minishell: ", 2);
    	// 	ft_putstr_fd(cmd->args[0], 2);
    	// 	ft_putstr_fd(": command no found\n", 2);
		// 	free(cmd->way);
		// }
		*flag = 1;
	}
	if (current->type == D_REDIR_IN)
	{
		*fd = current->fd_heredoc;
		*flag = 2;
	}
	if (current->type == REDIR_OUT || current->type == D_REDIR_OUT)
	{
		if (current->type == REDIR_OUT)
			*fd = open(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (current->type == D_REDIR_OUT)
			*fd = open(current->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		*flag = 3;
	}
}

void	redirection(t_cmd *cmd, t_data *data)
{
	t_redir	*current;
	int		fd;
	int		flag;

	fd = 0;
	current = cmd->redirs_list->head;
	flag = 0;
	while (current)
	{
		open_file(current, &fd, &flag);
		if (fd == -1 && current->type == D_REDIR_IN)
			ft_shell_exit(data);
		if (fd == -1 && current->type == REDIR_IN)
    {
      ft_free_data(data);
      exit(0);
    }
		if (flag == 1)
			dup2(fd, 0);
		if (flag == 2)
		{
			dup2(fd, 0);
			close(current->fd_heredoc);
		}
		if (flag == 3)
			dup2(fd, 1);
		if (fd != 0 && fd != 1)
			close(fd);
		current = current->next;
	}
}
