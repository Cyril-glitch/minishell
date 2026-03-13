/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 12:07:29 by cycolonn          #+#    #+#             */
/*   Updated: 2026/03/13 12:07:35 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env_list	*ft_key_hunter(char *args, t_env_list *env_list, t_data *data)
{
	t_env_list	*cur;
	t_env_list	*tmp;

	tmp = ft_new_env(args);
	if (!tmp)
		ft_shell_exit(data);
	cur = env_list;
	while (cur)
	{
		if (ft_strcmp(tmp->key, cur->key) == 0)
		{
			ft_lstclear_env(&tmp);
			return (cur);
		}
		cur = cur->next;
	}
	ft_lstclear_env(&tmp);
	return (NULL);
}

void	ft_del_env(t_env_list *todel, t_env_list **env_list)
{
	t_env_list	*prev;
	t_env_list	*next;

	if (*env_list == todel && !(*env_list)->next)
	{
		ft_lstclear_env(env_list);
		return ;
	}
	prev = todel->prev;
	next = todel->next;
	if (todel->line)
		free(todel->line);
	if (todel->key)
		free(todel->key);
	if (todel->content)
		free(todel->content);
	if (todel == *env_list)
		*env_list = next;
	free(todel);
	todel = NULL;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
}

int	ft_unset(char **args, t_env_list **env_list, t_data *data)
{
	int			i;
	t_env_list	*tmp;

	i = 1;
	tmp = NULL;
	while (args[i])
	{
		tmp = ft_key_hunter(args[i], *env_list, data);
		if (!ft_strcmp(args[i], "PATH"))
			data->unset = 1;
		if (tmp)
			ft_del_env(tmp, env_list);
		i++;
	}
	return (1);
}
