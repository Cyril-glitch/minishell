/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 12:10:56 by cycolonn          #+#    #+#             */
/*   Updated: 2026/03/13 12:10:58 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_add_signal(t_data *data)
{
	data->sig_a = malloc(sizeof(struct sigaction));
	if (!data->sig_a)
		ft_shell_exit(data);
	ft_interactive_mode(data->sig_a, data);
}

static void	ft_add_termios(t_data *data)
{
	data->orig_termios = malloc(sizeof(struct termios));
	if (!data->orig_termios)
		ft_shell_exit(data);
	data->new_termios = malloc(sizeof(struct termios));
	if (!data->new_termios)
		ft_shell_exit(data);
	ft_init_termios(data->orig_termios, data->new_termios);
}

static void	ft_add_prompt(t_data *data)
{
	data->prompt = malloc(sizeof(t_prompt));
	if (!data->prompt)
		ft_shell_exit(data);
	data->prompt->user = NULL;
	data->prompt->group = NULL;
	data->prompt->pwd = NULL;
	data->prompt->prompt = NULL;
}

t_data	*ft_init_data(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	g_sig_status = 0;
	data = malloc(sizeof(t_data));
	data->unset = 0;
	data->envi = 0;
	ft_add_termios(data);
	ft_add_signal(data);
	ft_add_env_list(data, env);
	ft_shlvl(&data->env_list, data);
	ft_my_env(data->env_list, data);
	ft_add_token_list(data);
	ft_add_cmd_list(data);
	ft_add_expand(data);
	data->expd_lst = NULL;
	data->last_exit_code = 0;
	data->child = 0;
	ft_add_prompt(data);
	data->fd_tmp = 0;
	data->doc_line = 0;
	return (data);
}
