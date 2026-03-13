/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 12:08:28 by cycolonn          #+#    #+#             */
/*   Updated: 2026/03/13 12:09:12 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_val_edge_case(char *str, t_expand *expd, t_data *data)
{
	if (!*str)
	{
		expd->val = ft_strdup("");
		if (!expd->val)
			ft_shell_exit(data);
		return (0);
	}
	if (*str && *str == '$' && *(str + 1) == 0)
	{
		expd->val = ft_strdup("$");
		return (1);
	}
	if (*str && *str == '$' && *(str + 1) == '?')
	{
		if (expd->quote == '\'')
			expd->val = ft_strdup("$?");
		else
			expd->val = ft_itoa(g_sig_status);
		if (!expd->val)
			ft_shell_exit(data);
		return (2);
	}
	return (-1);
}

void	ft_expd_zero(t_expand *expd)
{
	if (expd->prefix)
	{
		free(expd->prefix);
		expd->prefix = NULL;
	}
	if (expd->key)
	{
		free(expd->key);
		expd->key = NULL;
	}
	if (expd->val)
	{
		free(expd->val);
		expd->val = NULL;
	}
	if (expd->suffix)
	{
		free(expd->suffix);
		expd->suffix = NULL;
	}
	if (expd->cat)
	{
		free(expd->cat);
		expd->cat = NULL;
	}
}
