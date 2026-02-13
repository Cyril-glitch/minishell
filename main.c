/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtagand <mtagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 16:05:46 by mtagand           #+#    #+#             */
/*   Updated: 2026/02/13 16:26:41 by mtagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "./inc/minishell.h"

volatile  sig_atomic_t g_sig_status;

int main(int ac, char **av, char **env)
{
  (void)ac;
  (void)av;
  (void)env;
  struct sigaction	sig_a;
  struct termios orig_termios;
  struct termios new_termios;
  //t_env_list  *env_list;
  t_token_list token_list;
  char *line;

  ft_init_signal(&sig_a);
  ft_termios(&orig_termios, &new_termios);
  //env_list = ft_env_list(env);
  g_sig_status = 0;

  while (1)
  {
    line = readline("losmachinos:~$ ");
    if (!line)
      ft_shell_exit(NULL, NULL, orig_termios);
    add_history(line);
    lexer(line, &token_list);
  }
}
