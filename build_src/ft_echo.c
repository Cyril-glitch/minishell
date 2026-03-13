/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 12:06:17 by cycolonn          #+#    #+#             */
/*   Updated: 2026/03/13 12:06:21 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_isoption(char *s)
{
	int	i;

	i = 0;
	if (s[i] != '-')
		return (0);
	i++;
	while (s[i] == 'n')
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}

static int	ft_option(char **args)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (args[i])
	{
		if (ft_isoption(args[i]))
			count++;
		else
			return (count);
		i++;
	}
	return (count);
}

void	ft_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	i += ft_option(args);
	newline = (i < 2);
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		i++;
		if (args[i])
			write(1, " ", 1);
	}
	if (newline)
		write(1, "\n", 1);
}
