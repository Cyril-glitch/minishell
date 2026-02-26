/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 09:19:45 by mathis            #+#    #+#             */
/*   Updated: 2026/02/26 09:19:47 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_expd_zero(t_expand *expd)
{
	if (!expd)
		return ;
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
	expd->quote = 0;
}

void	ft_print_lst(t_list *lst)
{
	t_list	*current;

	current = NULL;
	current = lst;
	while (current)
	{
		printf("%s", (char *)current->content);
		current = current->next;
	}
	printf("\n");
}
