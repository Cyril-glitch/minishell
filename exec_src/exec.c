/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 09:07:41 by mathis            #+#    #+#             */
/*   Updated: 2026/02/25 21:42:22 by mathis           ###   ########.fr       */
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
		ft_unset(cmd->args, &data->env_list);
	if (cmd->build == ENV)
		ft_env(cmd->args, data->env_list);
	exit(1);
}

void	child(t_data *data, int *fd_pipe, t_cmd *cmd, char **env)
{
	ft_childmode(data->sig_a, data);
	pipex(cmd, data, fd_pipe);
	redirection(cmd, data);
	if (!cmd->is_build)
		execve(cmd->way, cmd->args, env);
	if (cmd->is_build == 2)
		exit(1);
	if (cmd->is_build == 1)
		exec_build(cmd, data);
}

int	exec_cmd(t_cmd *cmd, char **env, t_data *data)
{
	pid_t	pid;
	int		fd_pipe[2];
	int		status;

	if (cmd->build == CD)
		return (ft_cd(cmd->args[1], data->env_list, data));
	if (cmd->next)
		pipe(fd_pipe);
	pid = fork();
	if (pid == -1)
		ft_shell_exit(data);
	if (pid == 0)
		child(data, fd_pipe, cmd, env);
	ft_sigmute(data->sig_a);
	waitpid(pid, &status, 0);
	write(1, "\n", 1);
	ft_interactive_mode(data->sig_a, data);
	if (data->fd_tmp != 0)
		close(data->fd_tmp);
	if (cmd->next)
	{
		close(fd_pipe[1]);
		data->fd_tmp = fd_pipe[0];
	}
	return (1);
}

void	exec(t_cmd *cmd, char **env, t_data *data)
{
	char	**path_tab;

	if (cmd->build == EXIT)
		ft_exit(cmd->args, data);
	if (cmd->is_build == 0)
	{
		path_tab = parse_path(env);
		if (!path_tab)
			ft_shell_exit(data);
		cmd->way = find_way_path(path_tab, cmd->args[0], data);
		if (!cmd->way)
		{
			printf("command no found : %s\n", cmd->args[0]);
			ft_tabclear(path_tab);
			free(cmd->way);
			return ;
		}
	}
	exec_cmd(cmd, env, data);
}

void	execut(t_data *data, char **env)
{
	t_cmd	*current;

	check_heredoc(data->cmd_list, data);
	exec(data->cmd_list->head, env, data);
	current = data->cmd_list->head->next;
	while (current)
	{
		exec(current, env, data);
		current = current->next;
	}
	while (wait(NULL) > 0)
		;
	if (data->fd_tmp != 0)
		close(data->fd_tmp);
}
