/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtagand <mtagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 09:07:41 by mathis            #+#    #+#             */
/*   Updated: 2026/02/27 17:47:08 by mtagand          ###   ########.fr       */
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
	if (cmd->build == CD)
		ft_cd(&cmd->args[1], data->env_list, data);
	if (cmd->build == EXIT)
		ft_exit(cmd->args, data);
}

void	child(t_data *data, int *fd_pipe, t_cmd *cmd, char **env)
{
	ft_childmode(data->sig_a, data);
	pipex(cmd, data, fd_pipe);
	redirection(cmd, data);
	if (!cmd->is_build)
		execve(cmd->way, cmd->args, env);
	exec_build(cmd, data);
	ft_free_data(data);
	exit(0);
}

int	exec_cmd(t_cmd *cmd, char **env, t_data *data)
{
	pid_t	pid;
	int		fd_pipe[2];
    int save_in;
    int save_out;

	if (cmd->next)
		pipe(fd_pipe);
	if (cmd->next || !cmd->is_build)
	{	
		pid = fork();
		data->last_pid = pid;
		if (pid == -1)
			ft_shell_exit(data);
		if (pid == 0)
			child(data, fd_pipe, cmd, env);
	}
	else if (!cmd->next)
	{
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

	if (cmd->is_build == 0)
	{
		path_tab = parse_path(env);
		if (!path_tab)
			ft_shell_exit(data);
		cmd->way = find_way_path(path_tab, cmd->args[0], data);
		ft_tabclear(path_tab);
		if (!cmd->way)
		{
			printf("command no found : %s\n", cmd->args[0]);
			free(cmd->way);
			return ;
		}
	}
	//if (cmd->is_build == 0 || cmd->is_build == 1)
	exec_cmd(cmd, env, data);
}

void    execut(t_data *data, char **env)
{
    t_cmd    *current;
    int      status;

    status = 0;
    data->last_pid = -1;
    check_heredoc(data->cmd_list, data);
    if (g_sig_status == 130)
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
    while (wait(NULL) > 0)
        ;
    if (data->fd_tmp != 0)
        close(data->fd_tmp);
    ft_interactive_mode(data->sig_a, data);
}
