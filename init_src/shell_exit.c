#include "../inc/minishell.h"

void    ft_free_data(t_data *data)
{
    if (!data)
        return ;
    if (data->line)
        free(data->line);
    if (data->env_list)
        ft_lstclear_env(&data->env_list);
    if (data->token_list)
        ft_db_lstclear(data->token_list, free);
    if (data->sig_a)
        free(data->sig_a);
    if (data->orig_termios)
        free(data->orig_termios);
    if (data->new_termios)
        free(data->new_termios);
    free(data);
    data = NULL;
}

void	ft_shell_exit(t_data *data)
{
	tcsetattr(0, TCSANOW, data->orig_termios);
    ft_free_data(data);
	rl_clear_history();
	exit(0);
}
