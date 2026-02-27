/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtagand <mtagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 21:34:05 by mathis            #+#    #+#             */
/*   Updated: 2026/02/27 17:29:27 by mtagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	child_heredoc(t_data *data, t_redir *redir, int *fd, int next)
{
	char	*line;

	ft_childmode(data->sig_a, data);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			free(line);	
			if (next)
				ft_shell_exit_hd(data, redir->file);
			return ;
		}
		if (!ft_strcmp(line, redir->file))
		{
			free(line);
			if (next)
			{
				ft_free_data(data);
				exit(0);
			}
			return ;
		}
		ft_putstr_fd(line, fd[1]);
		write(fd[1], "\n", 1);
		free(line);
	}
}

void	d_redir_in(t_redir *redir, t_data *data, t_cmd *cmd)
{
	int		fd[2];
	pid_t	pid;
	
	pipe(fd);
	if (cmd->next)
	{
		
		pid = fork();
		if (pid == 0)
			child_heredoc(data, redir, fd, 1);
		//ft_sigmute(data->sig_a);
		waitpid(pid, &g_sig_status, 0);
		if (WIFEXITED(g_sig_status))
			g_sig_status = WEXITSTATUS(g_sig_status);
		else if (WIFSIGNALED(g_sig_status))
			g_sig_status = 128 + WTERMSIG(g_sig_status);
		//ft_interactive_mode(data->sig_a, data);
	}
	else 
		child_heredoc(data, redir, fd, 0);
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
				d_redir_in(current_redir, data, current_cmd);
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
