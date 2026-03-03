/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtagand <mtagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:28:53 by cycolonn          #+#    #+#             */
/*   Updated: 2026/03/03 17:40:26 by mtagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_envoid(t_env_list **env_list, t_data *data)
{
	char	*old[3];
	char	*pwd[3];
	char	*shlvl[3];
	char	*current_path;

	current_path = NULL;
	current_path = getcwd(current_path, PATH_MAX);
	if (!current_path)
	{
		perror("getcwd");
		ft_shell_exit(data);
	}
	old[0] = "export";
	old[1] = "OLDPWD";
	old[2] = NULL;
	pwd[0] = "export";
	pwd[1] = ft_strjoin("PWD=", current_path);
	pwd[2] = NULL;
	shlvl[0] = "export";
	shlvl[1] = "SHLVL=1";
	shlvl[2] = NULL;
	ft_export(old, env_list, data);
	ft_export(pwd, env_list, data);
	free(pwd[1]);
	ft_export(shlvl, env_list, data);
}

t_env_list	*ft_new_env(char *str)
{
	int			i;
	t_env_list	*new;

	i = 0;
	new = malloc(sizeof(t_env_list));
	if (!new)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	new->line = ft_strdup(str);
	new->key = ft_substr(str, 0, i);
	if (!str[i])
	{
		new->content = NULL;
		new->next = NULL;
		new->prev = NULL;
		return (new);
	}
	else
		new->content = ft_substr(str, (i + 1), ft_strlen(&str[i + 1]));
	new->next = NULL;
	new->prev = NULL;
	if (!new->line || !new->key || !new->content)
		return (NULL);
	return (new);
}

t_env_list	*ft_env_list(char **env, t_data *data)
{
	int			i;
	t_env_list	*env_list;
	t_env_list	*tmp;

	i = 0;
	env_list = NULL;
	tmp = NULL;
	if (!env[i])
		ft_envoid(&env_list, data);
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
