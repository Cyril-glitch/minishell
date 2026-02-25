/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 09:07:41 by mathis            #+#    #+#             */
/*   Updated: 2026/02/25 12:04:30 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void pipex(t_cmd *cmd, t_data *data, int *fd_pipe)
{
    if (data->fd_tmp != 0)
    {
        dup2(data->fd_tmp, 0);
        close(data->fd_tmp);
    }
    if (cmd->next)
    {
        dup2(fd_pipe[1], 1);
        close(fd_pipe[1]);
        close(fd_pipe[0]);
    }
}

void    exec_build(t_cmd *cmd, t_data *data)
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
    // METTRE FERMTURE ICI
    exit(1);
}

void    exec_cmd(t_cmd *cmd, char *way, char **env, t_data *data)
{
    pid_t pid;
    int fd_pipe[2];

    if (cmd->build == CD)
    {
        ft_cd(cmd->args[1], data->env_list, data);
        return ;
    }
    if (cmd->next)
        pipe(fd_pipe);
    pid = fork();
    if (pid == -1)
        ft_shell_exit(data);
    if (pid == 0)
    {
        // METTRE OUVERTURE
        pipex(cmd, data, fd_pipe);
        redirection(cmd, data);
        if (!cmd->is_build)
        {
            // METTRE ICI FERMETURE
            execve(way, cmd->args, env);
            exit(127);
        }
        if (cmd->is_build == 1)
            exec_build(cmd, data);
        if (cmd->is_build == 2)
        {
            // METTRE FERMTURE
            exit(1);
        }
    }
    if (data->fd_tmp != 0)
        close(data->fd_tmp);
    if (cmd->next)
    {
        close(fd_pipe[1]);
        data->fd_tmp = fd_pipe[0];
    }
    else
        data->fd_tmp = 0;
}

void    exec(t_cmd *cmd, char **env, t_data *data)
{
    char    **path_tab;
    char    *way;

    if (cmd->build == EXIT)
        ft_exit(cmd->args, data);
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
    }
    else
        way = NULL;
    exec_cmd(cmd, way, env, data);
}

void    d_redir_in(t_redir *redir, t_data *data)
{
    char *line;
    int fd[2];
    
    pipe(fd);
    while (1)
    {
        line = readline("> ");
        if (!line)
            ft_shell_exit(data);
        if (!ft_strcmp(line, redir->file))
        {
            free(line);
            break;
        }
        ft_putstr_fd(line, fd[1]);
        write(fd[1], "\n", 1);
        free(line);
    }
    close(fd[1]);
    redir->fd_heredoc = fd[0];
}

void    check_heredoc(t_cmd_list *cmd_list, t_data *data)
{
    t_cmd *current_cmd;
    t_redir *current_redir;

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

void execut(t_data *data, char **env)
{
    t_cmd				*current;

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
