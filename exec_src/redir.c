/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:26:44 by mathis            #+#    #+#             */
/*   Updated: 2026/02/19 13:32:36 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int    d_redir_in(char *str)
{
    char *line;
    int fd[2];

    pipe(fd);
    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            // fonction free
        }
        if (!ft_strcmp(line, str))
        {
            free(line);
            break;
        }
        ft_putstr_fd(line, fd[1]);
        write(fd[1], "\n", 1);
        free(line);
    }
    close(fd[1]);
    return(fd[0]);
}

void    open_file(t_redir *current, int *fd, int *flag)
{
        if (current->type == REDIR_IN || current->type == D_REDIR_IN)
        {
            if (current->type == REDIR_IN)
                *fd = open(current->file, O_RDONLY);
            if (current->type == D_REDIR_IN)
                *fd = d_redir_in(current->file);
            *flag = 1;
        }
        if (current->type == REDIR_OUT || current->type == D_REDIR_OUT)
        {
            if (current->type == REDIR_OUT)
                *fd = open(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (current->type == D_REDIR_OUT)
                *fd = open(current->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            *flag = 2;
        }
}

void    redirection(t_cmd *cmd)
{
    t_redir *current;
    int fd;
    int flag;

    fd = 0;
    current = cmd->redirs_list->head;
    flag = 0;
    while (current)
    {
        open_file(current, &fd, &flag);
        if (fd == -1)
        {
            //fonction free;
        }
        if (flag == 1)
            dup2(fd, 0);
        if (flag == 2)
            dup2(fd, 1);
        if (fd != 0 && fd != 1)
            close(fd);
        current = current->next;
    }
}
