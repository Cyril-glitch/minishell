/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 09:07:41 by mathis            #+#    #+#             */
/*   Updated: 2026/03/10 14:29:39 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec_build(t_cmd *cmd, t_data *data)
{
	if (cmd->build == ECHOO)
		ft_echo(cmd->args);
	if (cmd->build == PWD)
		ft_pwd(data->env_list);
	if (cmd->build == EXPORT)
		ft_export(cmd->args, &data->env_list, data);
	if (cmd->build == UNSET)
		ft_unset(cmd->args, &data->env_list, data);
	if (cmd->build == ENV)
		ft_env(cmd->args, data->env_list);
	if (cmd->build == CD)
		ft_cd(&cmd->args[1], data->env_list, data);
	if (cmd->build == EXIT)
		ft_exit(cmd, data);
  g_sig_status = 0;
}

void	child(t_data *data, int *fd_pipe, t_cmd *cmd, char **env)
{
	ft_childmode(data->sig_a, data);
	pipex(cmd, data, fd_pipe);
	redirection(cmd, data);
	if (cmd->build == DFL)
		execve(cmd->way, cmd->args, env);
	else
		exec_build(cmd, data);
	ft_free_data(data);
	exit(g_sig_status);
}

void	nofork(t_cmd *cmd, t_data *data)
{
	int		save_in;
	int		save_out;

	save_in = dup(0);
	save_out = dup(1);
	redirection(cmd, data);
	if (cmd->is_build == 1)
		exec_build(cmd, data);
	dup2(save_in, 0);
	dup2(save_out, 1);
	close(save_in);
	close(save_out);
}

int	exec_cmd(t_cmd *cmd, char **env, t_data *data)
{
	pid_t	pid;
	int		fd_pipe[2];

	if (cmd->next)
		pipe(fd_pipe);
	if (cmd->prev || cmd->next || !cmd->is_build || cmd->is_build == -1)
	{
		pid = fork();
		data->last_pid = pid;
		if (pid == -1)
			ft_shell_exit(data);
		if (pid == 0)
			child(data, fd_pipe, cmd, env);
	}
	else
		nofork(cmd, data);
	if (data->fd_tmp != 0)
		close(data->fd_tmp);
	if (cmd->next)
	{
		close(fd_pipe[1]);
		data->fd_tmp = fd_pipe[0];
	}
	return (1);
}

void	if_is_directory(t_cmd *cmd)
{
	struct stat	sb;

	stat(cmd->way, &sb);
	if (S_ISDIR(sb.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		g_sig_status = 126;
	}
}

void	exec(t_cmd *cmd, char **env, t_data *data)
{
	char		**path_tab;

	if (cmd->is_build == 0)
	{
		path_tab = parse_path(env);
		cmd->way = find_way_path(path_tab, cmd->args[0], data);
		if (path_tab)
			ft_tabclear(path_tab);
		if (!cmd->way)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			g_sig_status = 127;
			free(cmd->way);
			cmd->build = DFL2;
		}
		else
			if_is_directory(cmd);
	}
	exec_cmd(cmd, env, data);
}

void	get_status(t_data *data, int status)
{
	waitpid(data->last_pid, &status, 0);
	if (WIFEXITED(status))
		g_sig_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_sig_status = 128 + WTERMSIG(status);
		write(1, "\n", 1);
	}
}

void	execut(t_data *data, char **env)
{
	t_cmd	*current;
	int		status;

	status = 0;
	data->last_pid = -1;
	if (check_heredoc(data->cmd_list, data) == -1)
		return ;
	ft_sigmute(data->sig_a);
	exec(data->cmd_list->head, env, data);
	current = data->cmd_list->head->next;
	while (current)
	{
		exec(current, env, data);
		current = current->next;
	}
	if (data->last_pid > 0)
		get_status(data, status);
	while (wait(NULL) > 0)
		;
	if (data->fd_tmp != 0)
		close(data->fd_tmp);
	ft_interactive_mode(data->sig_a, data);
}
