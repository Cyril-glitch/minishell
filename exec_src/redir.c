/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:26:44 by mathis            #+#    #+#             */
/*   Updated: 2026/03/10 14:54:21 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	for_redir_in(t_redir *current, int *fd, t_cmd *cmd, int *flag)
{
	*fd = open(current->file, O_RDONLY);
	if (*fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(current->file, 2);
		if (errno == ENOENT)
			ft_putstr_fd(": No such file or directory\n", 2);
		else if (errno == EACCES)
			ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (!cmd->way && cmd->build == DFL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command no found\n", 2);
		free(cmd->way);
	}
	*flag = 1;
}

void	open_file(t_redir *current, int *fd, int *flag, t_cmd *cmd)
{
	if (current->type == REDIR_IN)
		for_redir_in(current, fd, cmd, flag);
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
		if (*fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(current->file, 2);
			ft_putstr_fd(": Permission denied\n", 2);
		}
	}
}

void	flag_exit_and_close(int fd, t_redir *current, t_data *data, int flag)
{
	if (fd == -1 && current->type == D_REDIR_IN)
		ft_shell_exit(data);
	if (fd == -1 && (current->type == REDIR_IN || current->type == REDIR_OUT
			|| current->type == D_REDIR_OUT))
	{
		ft_free_data(data);
		exit(1);
	}
	if (flag == 1)
		dup2(fd, 0);
	if (flag == 2)
	{
		dup2(fd, 0);
		close(current->fd_heredoc);
		current->fd_heredoc = -1;
	}
	if (flag == 3)
		dup2(fd, 1);
	if (fd != 0 && fd != 1)
		close(fd);
}

void	redirection(t_cmd *cmd, t_data *data)
{
	t_redir	*current;
	int		fd;
	int		flag;

	current = cmd->redirs_list->head;
	fd = 0;
	flag = 0;
	while (current)
	{
		open_file(current, &fd, &flag, cmd);
		flag_exit_and_close(fd, current, data, flag);
		current = current->next;
	}
}
