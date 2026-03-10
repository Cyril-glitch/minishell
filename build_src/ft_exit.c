/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtagand <mtagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:17:13 by mathis            #+#    #+#             */
/*   Updated: 2026/03/09 15:29:35 by mtagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

long long	ft_atoll(const char *nbr)
{
	int			i;
	int			signe;
	long long	res;

	i = 0;
	signe = 1;
	res = 0;
	while (ft_isspace(nbr[i]))
		i++;
	if (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			signe = -1;
		i++;
	}
	while (ft_isdigit(nbr[i]))
	{
		res *= 10;
		res += nbr[i] - '0';
		i++;
	}
	return (res * signe);
}

int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	ft_shell_exit_special(t_data *data, int value)
{
	tcsetattr(0, TCSANOW, data->orig_termios);
	ft_free_data(data);
	rl_clear_history();
	exit(value);
}

int	check_value_exit(char *args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (args[j] == '-')
		j++;
	while (args[i + j])
		i++;
	if (i > 19)
		return (0);
	if (j)
	{
		if (!ft_strcmp(args, "9223372036854775807"))
			return (0);
	}
	else
	{
		if (!ft_strcmp(args, "-9223372036854775808"))
			return (0);
	}
	return (1);
}

int	ft_exit_utils(char **args, t_data *data)
{
	if (tablen(args) > 2)
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
		printf("arg = %lld\n", ft_atoll(args[1]));
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
