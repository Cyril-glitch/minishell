/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:17:13 by mathis            #+#    #+#             */
/*   Updated: 2026/03/10 14:12:19 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_shell_exit_special(t_data *data, int value)
{
	tcsetattr(0, TCSANOW, data->orig_termios);
	ft_free_data(data);
	rl_clear_history();
	exit(value);
}

int	lookandreturn(char *args, int j, int k)
{
	if (!j && !k)
	{
		if (ft_strcmp(args, "9223372036854775807") > 0)
			return (0);
	}
	else if (k)
	{
		if (ft_strcmp(args, "+9223372036854775807") > 0)
			return (0);
	}
	else if (j)
	{
		if (ft_strcmp(args, "-9223372036854775808") > 0)
			return (0);
	}
	return (1);
}

int	check_value_exit(char *args)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	if (args[j] == '-')
		j++;
	if (args[k] == '+')
		k++;
	while (args[i + j + k])
		i++;
	if (i > 19)
		return (0);
	if (!lookandreturn(args, j, k))
		return (0);
	return (1);
}

int	ft_exit_utils(char **args, t_data *data)
{
	if (ft_tablen(args) > 2)
	{
		ft_putstr_fd("exit\nminishell: too many arguments\n", 2);
		g_sig_status = 1;
		return (0);
	}
	if (!check_value_exit(args[1]))
	{
		ft_putstr_fd("exit\nminishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argement required\n", 2);
		ft_shell_exit_special(data, 2);
	}
	if (ft_atoll(args[1]) < 0)
	{
		ft_putstr_fd("exit\n", 1);
		ft_shell_exit_special(data, 256 + (ft_atoll(args[1]) % 256));
	}
	if (ft_atoi(args[1]) > 255)
	{
		ft_putstr_fd("exit\n", 1);
		ft_shell_exit_special(data, ft_atoi(args[1]) % 256);
	}
	return (1);
}

void	ft_exit(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 1;
	if (!cmd->args[1])
	{
		if (!cmd->prev && !cmd->next)
			ft_putstr_fd("exit\n", 1);
		ft_shell_exit_special(data, g_sig_status);
	}
	while (cmd->args[1][i])
	{
		if (!ft_isdigit(cmd->args[1][i]))
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(cmd->args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			ft_shell_exit_special(data, 2);
		}
		i++;
	}
	if (!ft_exit_utils(cmd->args, data))
		return ;
	if (!cmd->prev && !cmd->next)
		ft_putstr_fd("exit\n", 1);
	ft_shell_exit_special(data, ft_atoi(cmd->args[1]));
}
