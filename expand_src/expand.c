/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtagand <mtagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 09:19:40 by mathis            #+#    #+#             */
/*   Updated: 2026/02/27 12:25:59 by mtagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static size_t	ft_newlen(t_list *expd_lst)
{
	size_t	len;
	t_list	*current;

	len = 0;
	current = expd_lst;
	while (current)
	{
		len += ft_strlen((char *)current->content);
		current = current->next;
	}
	return (len);
}

static void	ft_expanded(t_token *token_lst, t_list *expd_lst, t_data *data)
{
	size_t	len;
	size_t	i;
	size_t	j;
	t_list	*current;

	j = 0;
	i = 0;
	len = 0;
	len = ft_newlen(expd_lst);
	current = expd_lst;
	free(token_lst->content);
	token_lst->content = malloc(sizeof(char) * (len + 1));
	if (!token_lst->content)
		ft_shell_exit(data);
	while (current)
	{
		i = 0;
		while (((char *)current->content)[i])
		{
			token_lst->content[j] = ((char *)current->content)[i];
			i++;
			j++;
		}
		token_lst->content[j] = 0;
		current = current->next;
	}
}

void	ft_expand(t_token *token_lst, t_env_list *env_lst, t_data *data)
{
	t_token	*current;

	current = token_lst;
	while (current)
	{
		ft_subtitute(current->content, current, env_lst, data);
		ft_expanded(current, data->expd_lst, data);
		ft_lstclear(&data->expd_lst, free);
		current = current->next;
	}
}
