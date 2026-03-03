/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sig_term.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtagand <mtagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:29:05 by cycolonn          #+#    #+#             */
/*   Updated: 2026/03/03 12:57:31 by mtagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_signal_handler(int signum, siginfo_t *client, void *context)
{
	(void)context;
	(void)client;
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_sig_status = 130;
	}
}

void	ft_childmode(struct sigaction *sig_a, t_data *data)
{
	tcsetattr(0, TCSANOW, data->orig_termios);
	sig_a->sa_flags = 0;
	sig_a->sa_handler = SIG_DFL;
	sigemptyset(&sig_a->sa_mask);
	sigaction(SIGINT, sig_a, NULL);
	sigaction(SIGQUIT, sig_a, NULL);
	data->child = 1;
}

void	ft_sigmute(struct sigaction *sig_a)
{
	sig_a->sa_flags = 0;
	sig_a->sa_handler = SIG_IGN;
	sigemptyset(&sig_a->sa_mask);
	sigaction(SIGINT, sig_a, NULL);
	sigaction(SIGQUIT, sig_a, NULL);
}

void	ft_interactive_mode(struct sigaction *sig_a, t_data *data)
{
	tcsetattr(0, TCSANOW, data->orig_termios);
	sig_a->sa_flags = SA_SIGINFO;
	sig_a->sa_sigaction = ft_signal_handler;
	sigemptyset(&sig_a->sa_mask);
	sigaction(SIGINT, sig_a, NULL);
	sig_a->sa_flags = 0;
	sig_a->sa_handler = SIG_IGN;
	sigaction(SIGQUIT, sig_a, NULL);
	data->child = 0;
}

void	ft_init_termios(struct termios *orig_termios,
		struct termios *new_termios)
{
	tcgetattr(0, orig_termios);
	*new_termios = *orig_termios;
	new_termios->c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, new_termios);
}
