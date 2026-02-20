/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 16:05:46 by mtagand           #+#    #+#             */
/*   Updated: 2026/02/20 10:50:38 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

volatile sig_atomic_t	g_sig_status;

int	main(int ac, char **av, char **env)
{
  t_data *data;

  data = ft_init_data(ac,av,env);
  while (1)
  {
    data->fd_tmp = 0;
    data->line = readline("losmachinos:~$ ");
    if (!data->line)
      ft_shell_exit(data);
    if (ft_strcmp(data->line, "cd") == 0)
    {
      ft_cd("/home/cycolonn/M3/minishelihhgyyguygfjyfufgl/parser_src", data->env_list, data);
      ft_pwd(data->env_list);
    }
    add_history(data->line);
    lexer(data);
    ft_expand(data->token_list->head, data->env_list,data);
    parser(data);
    execut(data, env);
    ft_db_lstclear_token(data->token_list, free);
    ft_db_lstclear_cmd(data->cmd_list, free);
    free(data->line);
	}
}
