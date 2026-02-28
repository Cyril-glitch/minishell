/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtagand <mtagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 21:34:05 by mathis            #+#    #+#             */
/*   Updated: 2026/02/27 17:48:43 by mtagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	child_heredoc(t_data *data, t_redir *redir, int *fd)
{
	char	*line;

    ft_heredoc_mode(data->sig_a, data);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			free(line);	
			ft_shell_exit_hd(data, redir->file);
		}
		if (!ft_strcmp(line, redir->file))
		{
			free(line);
			ft_free_data(data);
			exit(0);
			return ;
		}
		ft_putstr_fd(line, fd[1]);
		write(fd[1], "\n", 1);
		free(line);
	}
}

void	d_redir_in(t_redir *redir, t_data *data)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);	
		child_heredoc(data, redir, fd);
	}
	ft_sigmute(data->sig_a);	
	waitpid(pid, &status, 0); 
	if (WIFEXITED(status))
		g_sig_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_sig_status = 128 + WTERMSIG(status);	
	ft_interactive_mode(data->sig_a, data);
	close(fd[1]);
	redir->fd_heredoc = fd[0];
}

void	check_heredoc(t_cmd_list *cmd_list, t_data *data)
{
	t_cmd	*current_cmd;
	t_redir	*current_redir;

	current_cmd = cmd_list->head;
	while (current_cmd)
	{
		current_redir = current_cmd->redirs_list->head;
		while (current_redir)
		{
			if (current_redir->type == D_REDIR_IN)
				d_redir_in(current_redir, data);
			current_redir = current_redir->next;
		}
		current_cmd = current_cmd->next;
	}
}

void	pipex(t_cmd *cmd, t_data *data, int *fd_pipe)
{
	dup2(data->fd_tmp, 0);
	if (data->fd_tmp != 0)
		close(data->fd_tmp);
	if (cmd->next)
	{
		dup2(fd_pipe[1], 1);
		close(fd_pipe[1]);
		close(fd_pipe[0]);
	}
}
