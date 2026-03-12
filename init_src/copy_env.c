/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtagand <mtagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:28:53 by cycolonn          #+#    #+#             */
/*   Updated: 2026/03/11 16:00:07 by mtagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_my_env(t_env_list *env_list, t_data *data)
{
	int			i;
	char		**my_env;
	t_env_list	*tmp;

	i = 0;
	tmp = env_list;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	my_env = malloc(sizeof(char *) * (i + 1));
	if (!my_env)
		ft_shell_exit(data);
	i = 0;
	while (env_list)
	{
		my_env[i] = ft_strdup(env_list->line);
		if (!my_env[i])
			ft_shell_exit(data);
		env_list = env_list->next;
		i++;
	}
	my_env[i] = NULL;
	data->my_env = my_env;
}

void	ft_shlvl(t_env_list **env_list, t_data *data)
{
	int			lvl;
	char		*tmp;
	t_env_list	*dup;

	lvl = 0;
	tmp = NULL;
	dup = ft_key_hunter("SHLVL", *env_list, data);
	if (dup)
	{
		lvl = ft_atoi(dup->content);
		free(dup->line);
		free(dup->content);
		dup->content = ft_itoa((lvl + 1));
		tmp = ft_strjoin(dup->key, "=");
		if (!tmp)
			ft_shell_exit(data);
		dup->line = ft_strjoin(tmp, dup->content);
	}
	free(tmp);
}

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
	{
		ft_envoid(&env_list, data);
		data->envi = 1;
	}
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
