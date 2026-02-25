 #include "../inc/minishell.h"

static void ft_add_signal(t_data *data)
{
  struct sigaction	*sig_a;

  sig_a = malloc(sizeof(struct sigaction));
  data->sig_a = sig_a;
  ft_interactive_mode(data->sig_a, data);
}

static void    ft_add_termios(t_data *data)
{
    struct termios *orig_termios;
    struct termios *new_termios;

    orig_termios = malloc(sizeof(struct termios));
    new_termios = malloc(sizeof(struct termios));
    data->orig_termios = orig_termios;
    data->new_termios = new_termios;
    ft_init_termios(data->orig_termios, data->new_termios);
}


t_data *ft_init_data(int ac, char **av, char **env)
{
  (void)ac;
  (void)av;
  t_data *data;

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
  data->prompt = NULL;
  data->fd_tmp = 0;
  return data;
}
