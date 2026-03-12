/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:12:55 by mathis            #+#    #+#             */
/*   Updated: 2026/03/12 12:15:20 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_token_list	*ft_add_split_token_lst(void)
{
	t_token_list	*new;

	new = malloc(sizeof(t_token_list));
	if (!new)
		return (NULL);
	new->head = NULL;
	new->tail = NULL;
	new->size = 0;
	return (new);
}

static int	ft_q_status(char quote, char c)
{
	if (!quote && (c == '\'' || c == '\"'))
		return (c);
	else if (quote && c == quote)
		return (0);
	return (quote);
}

static int	ft_single(t_token *new, char *str, t_data *data)
{
	if (!str)
		return (0);
	if (!ft_strcmp(str, "\'"))
	{
		new->content = ft_strdup("\'");
		if (!new->content)
			ft_shell_exit(data);
		return (1);
	}
	if (!ft_strcmp(str, "\""))
	{
		new->content = ft_strdup("\"");
		if (!new->content)
			ft_shell_exit(data);
		return (1);
	}
	return (0);
}

static void	ft_splitoken(t_token *cur, char *str, t_token_list *newlst,
		t_data *data)
{
	t_token	*new;
	char	*tmp;
	int		i;

	i = 0;
	new = ft_db_lstnew_token();
	if (!new)
		ft_shell_exit(data);
	while (str[i] && (str[i] != ' ' || data->quote))
		data->quote = ft_q_status(data->quote, str[i++]);
	tmp = ft_substr(str, 0, i);
	if (!tmp)
		ft_shell_exit(data);
	if (!ft_single(new, str, data))
		new->content = ft_delquote(tmp);
	new->type = cur->type;
	if (!new)
		ft_shell_exit(data);
	free(tmp);
	ft_db_lstadd_back_token(newlst, new);
	str += (i + (str[i] == ' '));
	if (*str)
		ft_splitoken(cur, str, newlst, data);
}

void	ft_split_expand(t_token_list *lst, t_data *data)
{
	t_token			*current;
	t_token_list	*newlst;

	current = lst->head;
	newlst = ft_add_split_token_lst();
	if (!newlst)
		ft_shell_exit(data);
	while (current)
	{
		data->quote = 0;
		ft_splitoken(current, current->content, newlst, data);
		current = current->next;
	}
	ft_db_lstclear_token(data->token_list, free);
	free(data->token_list);
	data->token_list = newlst;
}
