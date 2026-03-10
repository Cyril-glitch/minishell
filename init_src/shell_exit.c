/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 09:26:32 by mathis            #+#    #+#             */
/*   Updated: 2026/03/10 14:13:59 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_prompt(t_data *data)
{
	if (data->prompt->user)
		free(data->prompt->user);
	if (data->prompt->group)
		free(data->prompt->group);
	if (data->prompt->pwd)
		free(data->prompt->pwd);
	if (data->prompt->prompt)
		free(data->prompt->prompt);
}

static void	ft_free_list(t_data *data)
{
	if (data->env_list)
		ft_lstclear_env(&data->env_list);
	if (data->expd_lst)
		ft_lstclear(&data->expd_lst, free);
	if (data->token_list)
	{
		ft_db_lstclear_token(data->token_list, free);
		free(data->token_list);
	}
	if (data->cmd_list)
	{
		ft_db_lstclear_cmd(data->cmd_list, free);
		free(data->cmd_list);
	}
}

void	ft_free_data(t_data *data)
{
	ft_free_list(data);
	if (data->prompt)
	{
		ft_free_prompt(data);
		free(data->prompt);
	}
	if (data->line)
		free(data->line);
	if (data->sig_a)
		free(data->sig_a);
	if (data->orig_termios)
		free(data->orig_termios);
	if (data->new_termios)
		free(data->new_termios);
	if (data->expd)
	{
		ft_expd_zero(data->expd);
		data->expd->quote = 0;
		free(data->expd);
	}
	if (data->my_env)
		ft_tabclear(data->my_env);
	free(data);
	data = NULL;
}

void	ft_shell_exit(t_data *data)
{
	if (!data->child)
		tcsetattr(0, TCSANOW, data->orig_termios);
	if (!data->child)
		rl_clear_history();
	ft_putstr("exit\n");
	ft_free_data(data);
	exit(g_sig_status);
}

void	ft_shell_exit_hd(t_data *data, char *file)
{
	char	*nbr_line;

	if (g_sig_status == 130)
	{
		ft_free_data(data);
		exit(130);
	}
	ft_putstr_fd("warning: here-document at line ", 2);
	nbr_line = ft_itoa(data->doc_line);
	if (nbr_line)
	{
		ft_putstr_fd(nbr_line, 2);
		free(nbr_line);
	}
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd("\')\n", 2);
	ft_free_data(data);
	exit(g_sig_status);
}
