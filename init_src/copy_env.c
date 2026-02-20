/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:28:53 by cycolonn          #+#    #+#             */
/*   Updated: 2026/02/13 10:28:57 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env_list	*ft_new_env(char *str)
{
	int			i;
	t_env_list	*new;

	i = 0;
	new = malloc(sizeof(t_env_list));
	if (!new)
		return (NULL);
	while (str[i] != '=')
		i++;
	new->line = strdup(str);
	new->key = ft_substr(str, 0, i);
	new->content = ft_substr(str, (i + 1), ft_strlen(&str[i + 1]));
	new->next = NULL;
	if (!new->line || !new->key || !new->content)
		return (ft_clear_node_env(new), (NULL));
	return (new);
}

t_env_list	*ft_env_list(char **env)
{
	int			i;
	t_env_list	*env_list;
	t_env_list	*tmp;

	i = 0;
	env_list = NULL;
	tmp = NULL;
	while (env[i])
	{
		tmp = ft_new_env(env[i]);
		if (!tmp)
			return (ft_lstclear_env(&env_list), (NULL));
		ft_lstadd_back_env(&env_list, tmp);
		i++;
	}
	return (env_list);
}
