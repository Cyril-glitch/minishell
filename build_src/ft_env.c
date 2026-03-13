/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 12:06:37 by cycolonn          #+#    #+#             */
/*   Updated: 2026/03/13 12:06:44 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_printenv(t_env_list *lst)
{
	while (lst)
	{
		if (lst->content && *lst->content)
		{
			ft_putstr(lst->line);
			write(1, "\n", 1);
		}
		lst = lst->next;
	}
}

void	ft_env(char **args, t_env_list *env_list)
{
	int	i;

	i = 1;
	if (args[i])
	{
		ft_putstr_fd("losmaquinos: env: `", 2);
		ft_putstr_fd(args[i], 2);
		ft_putstr_fd("': No such file or directory\n", 2);
		g_sig_status = 127;
		return ;
	}
	ft_printenv(env_list);
}
