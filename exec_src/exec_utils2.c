/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:39:49 by mathis            #+#    #+#             */
/*   Updated: 2026/03/10 14:44:05 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
