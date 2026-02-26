/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 09:26:32 by mathis            #+#    #+#             */
/*   Updated: 2026/02/26 09:26:34 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_data(t_data *data)
{
	if (data->prompt)
		free(data->prompt);
	if (data->line)
		free(data->line);
	if (data->env_list)
		ft_lstclear_env(&data->env_list);
	if (data->token_list)
		ft_db_lstclear_token(data->token_list, free);
	if (data->cmd_list)
		ft_db_lstclear_cmd(data->cmd_list, free);
	if (data->sig_a)
		free(data->sig_a);
	if (data->orig_termios)
		free(data->orig_termios);
	if (data->new_termios)
		free(data->new_termios);
	if (data->expd)
	{
		ft_expd_zero(data->expd);
		free(data->expd);
	}
	if (data->expd_lst)
		ft_lstclear(&data->expd_lst, free);
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
	exit(0);
}

void	ft_shell_exit_hd(t_data *data, char *file)
{
  if (!data->child)
	  tcsetattr(0, TCSANOW, data->orig_termios);
  else
	  tcsetattr(0, TCSANOW, data->new_termios);
  if (!data->child)
	  rl_clear_history();
  ft_putstr_fd("warning: here-document at line 1 delimited by end-of-file (wanted `", 2);
  ft_putstr_fd(file, 2);
  ft_putstr_fd("\')\n", 2);
  ft_free_data(data);
	exit(0);
}
