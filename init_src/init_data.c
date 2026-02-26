/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 21:05:09 by mathis            #+#    #+#             */
/*   Updated: 2026/02/26 13:32:49 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_add_signal(t_data *data)
{
	struct sigaction	*sig_a;

	sig_a = malloc(sizeof(struct sigaction));
	if (!sig_a)
		ft_shell_exit(data);
	data->sig_a = sig_a;
	ft_interactive_mode(data->sig_a, data);
}

static void	ft_add_termios(t_data *data)
{
	struct termios	*orig_termios;
	struct termios	*new_termios;

	orig_termios = malloc(sizeof(struct termios));
	if (orig_termios)
		ft_shell_exit(data);
	new_termios = malloc(sizeof(struct termios));
	if (!new_termios)
		ft_shell_exit(data);
	data->orig_termios = orig_termios;
	data->new_termios = new_termios;
	ft_init_termios(data->orig_termios, data->new_termios);
}
static void ft_add_prompt(t_data *data)
{
	data->prompt = malloc(sizeof(t_prompt));
	if (!data->prompt)
		ft_shell_exit(data);
	data->prompt->user =NULL;
	data->prompt->group =NULL;
	data->prompt->pwd =NULL;
	data->prompt->prompt=NULL;
}

t_data	*ft_init_data(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	g_sig_status = 0;
	data = malloc(sizeof(t_data));
	ft_add_termios(data);
	ft_add_signal(data);
	ft_add_env_list(data, env);
	ft_add_token_list(data);
	ft_add_cmd_list(data);
	ft_add_expand(data);
	data->expd_lst = NULL;
	data->last_exit_code = 0;
	data->child = 0;
	ft_add_prompt(data);
	data->fd_tmp = 0;
	return (data);
}
