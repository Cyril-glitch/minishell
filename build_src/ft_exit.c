/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:17:13 by mathis            #+#    #+#             */
/*   Updated: 2026/02/23 16:34:35 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

long long	ft_atoll(const char *nbr)
{
	int		i;
	int		signe;
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

int tablen(char **tab)
{
    int i;

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

void    ft_exit(char **args, t_data *data)
{
    int i;

    i = 0;
    if (!args[1])
    {
        ft_putstr_fd("exit\n", 1);
        ft_shell_exit_special(data, 0);
    }
    while (args[1][i])
    {
        if (!ft_isdigit(args[1][i]))
        {
            ft_putstr_fd("exit\nminishell: exit: ", 2);
            ft_putstr_fd(args[1], 2);
            ft_putstr_fd(": numeric argument required\n", 2);
            ft_shell_exit_special(data, 1);
        }
        i++;
    }
    if (tablen(args) > 2)
    {
        ft_putstr_fd("exit\nminishell: too many arguments\n", 2);
        return;
    }
    if (atoll(args[1]) > 9223372036854775807)
    {
        ft_putstr_fd("exit\nminishell: too many arguments\n", 2);
        ft_shell_exit_special(data, 255);
    }
    if (atol(args[1]) < 0)
    {
        ft_putstr_fd("exit\n", 1);
        ft_shell_exit_special(data, 255);
    }
    if (atoi(args[1]) > 255)
    {
        ft_putstr_fd("exit\n", 1);
        ft_shell_exit_special(data, 1);
    }
    ft_putstr_fd("exit\n", 1);
    ft_shell_exit_special(data, atoi(args[1]));
}
