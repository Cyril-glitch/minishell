/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 09:19:33 by mathis            #+#    #+#             */
/*   Updated: 2026/03/10 15:31:03 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_quote_status(t_expand *expd, char c)
{
	if (!expd->quote && (c == '\'' || c == '\"'))
	{
		expd->quote = c;
		return (1);
	}
	else if (expd->quote && c == expd->quote)
	{
		expd->quote = 0;
		return (1);
	}
	return (0);
}

static int	new_len(char *s)
{
	int		i;
	int		len;
	char	quote;

	i = 0;
	len = 0;
	quote = 0;
	while (s[i])
	{
		if (!quote && (s[i] == '\'' || s[i] == '\"'))
			quote = s[i];
		else if (quote && s[i] == quote)
			quote = 0;
		else
			len++;
		i++;
	}
	return (len);
}

char	*ft_delquote(char *s)
{
	int		i;
	int		j;
	int		len;
	char	quote;
	char	*res;

	i = 0;
	j = 0;
	quote = 0;
	len = new_len(s);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (s[i])
	{
		if (!quote && (s[i] == '\'' || s[i] == '\"'))
			quote = s[i];
		else if (quote && s[i] == quote)
			quote = 0;
		else
			res[j++] = s[i];
		i++;
	}
	res[j] = 0;
	return (res);
}
