/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 09:07:41 by mathis            #+#    #+#             */
/*   Updated: 2026/02/20 12:42:53 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void pipex(t_cmd *cmd, t_data *data, int *fd_pipe)
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

void    exec_cmd(t_cmd *cmd, char *way, char **env, t_data *data)
{
    pid_t pid;
    int fd_pipe[2];

    if (cmd->next)
        pipe(fd_pipe);
    pid = fork();
    if (pid == -1)
        ft_shell_exit(data);
    if (pid == 0)
    {
        pipex(cmd, data, fd_pipe);
        redirection(cmd, data);
        execve(way, cmd->args, env);
    }
    if (data->fd_tmp != 0)
        close(data->fd_tmp);
    if (cmd->next)
    {
        close(fd_pipe[1]);
        data->fd_tmp = fd_pipe[0];
    }
}

void    exec(t_cmd *cmd, char **env, t_data *data)
{
    char    **path_tab;
    char    *way;

    if (cmd->is_build == 0)
    {
        path_tab = parse_path(env);
        if (!path_tab)
            ft_shell_exit(data);
        way = find_way_path(path_tab, cmd->args[0], data);
        if (!way)
        {
            printf("command no found : %s\n", cmd->args[0]);
            ft_tabclear(path_tab);
            free(way);
            return ;
        }
        exec_cmd(cmd, way, env, data);
    }
    else
    {
        //exec_build();
    }
}

void execut(t_data *data, char **env)
{
    t_cmd				*current;

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
