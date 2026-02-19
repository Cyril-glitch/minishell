/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 09:07:41 by mathis            #+#    #+#             */
/*   Updated: 2026/02/19 13:15:52 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void pipex(t_cmd *cmd, int *fd_tmp, int *fd_pipe)
{
    dup2(*fd_tmp, 0);
    if (*fd_tmp != 0)
        close(*fd_tmp);
    if (cmd->next)
    {
        dup2(fd_pipe[1], 1);
        close(fd_pipe[1]);
        close(fd_pipe[0]);
    }
}

void    exec_cmd(t_cmd *cmd, char *way, char **env, int *fd_tmp)
{
    pid_t pid;
    int fd_pipe[2];

    if (cmd->next)
        pipe(fd_pipe);
    pid = fork();
    if (pid == -1)
    {
        // fonction free;
    }
    if (pid == 0)
    {
        pipex(cmd, fd_tmp, fd_pipe);
        redirection(cmd);
        execve(way, cmd->args, env);
    }
    if (*fd_tmp != 0)
        close(*fd_tmp);
    if (cmd->next)
    {
        close(fd_pipe[1]);
        *fd_tmp = fd_pipe[0];
    }
}

void    exec(t_cmd *cmd, char **env, int *fd_tmp)
{
    char    **path_tab;
    char    *way;

    if (cmd->is_build == 0)
    {
        path_tab = parse_path(env);
        way = find_way_path(path_tab, cmd->args[0]);
        if (!way)
        {
            printf("command no found : %s\n", cmd->args[0]);
            ft_tabclear(path_tab);
            free(way);
            return ;
            //fonction free
        }
        exec_cmd(cmd, way, env, fd_tmp);
    }
    else
    {
        //exec_build();
    }
}
