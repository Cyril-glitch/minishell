#include "../inc/minishell.h"

static void	ft_heredoc_handler(int signum, siginfo_t *client, void *context)
{
	(void)context;
	(void)client;
	if (signum == SIGINT)
	{
		g_sig_status = 130;
		close(0);
		write(1, "\n", 1);
	}
}

void	ft_heredoc_mode(struct sigaction *sig_a, t_data *data)
{
	tcsetattr(0, TCSANOW, data->orig_termios);
	sig_a->sa_flags = SA_SIGINFO;
	sig_a->sa_sigaction = ft_heredoc_handler;
	sigemptyset(&sig_a->sa_mask);
	sigaction(SIGINT, sig_a, NULL);
	sig_a->sa_flags = 0;
	sig_a->sa_handler = SIG_IGN;
	sigaction(SIGQUIT, sig_a, NULL);
	data->child = 1;
}
