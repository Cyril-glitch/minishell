/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 16:05:46 by mtagand           #+#    #+#             */
/*   Updated: 2026/03/12 15:53:56 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

int	g_sig_status;

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	data = ft_init_data(ac, av, env);
	while (1)
	{
		ft_tabclear(data->my_env);
		ft_my_env(data->env_list, data);
		data->fd_tmp = 0;
		data->line = readline(ft_prompt_pwd(data->env_list, data));
		if (!data->line)
			ft_shell_exit(data);
		if (ft_strlen(data->line))
			add_history(data->line);
		lexer(data);
		ft_expand(data->token_list, data->env_list, data);
		if (parser(data))
			execut(data, data->my_env);
		ft_db_lstclear_token(data->token_list, free);
		ft_db_lstclear_cmd(data->cmd_list, free);
		data->doc_line++;
		free(data->line);
	}
}
