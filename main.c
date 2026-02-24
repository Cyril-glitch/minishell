/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 16:05:46 by mtagand           #+#    #+#             */
/*   Updated: 2026/02/23 12:40:32 by mathis           ###   ########.fr       */
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
    data->line = readline(ft_prompt_pwd(data->env_list, data));
    if (!data->line)
      ft_shell_exit(data);
    add_history(data->line);
    lexer(data);
    ft_expand(data->token_list->head, data->env_list,data);
    if (parser(data))
      execut(data, env);
    ft_db_lstclear_token(data->token_list, free);
    ft_db_lstclear_cmd(data->cmd_list, free);
    free(data->line);
  }
}
