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

static void ft_test_build(char *line, t_data *data)
{
    char **args;

    args = ft_split(line, ' ');
    if (ft_strcmp(args[0], "cd") == 0)
        ft_cd(args[1], data->env_list, data);
    if (ft_strcmp(args[0], "pwd") == 0)
        ft_pwd(data->env_list);
    if (ft_strcmp(args[0], "export") == 0)
        ft_export(args, &data->env_list, data);
}

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
    add_history(data->line);
    ft_test_build(data->line, data);
    lexer(data);
    ft_expand(data->token_list->head, data->env_list,data);
    parser(data);
    execut(data, env);
    ft_db_lstclear_token(data->token_list, free);
    ft_db_lstclear_cmd(data->cmd_list, free);
    free(data->line);
	}
}
