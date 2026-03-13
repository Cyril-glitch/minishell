/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 12:05:32 by cycolonn          #+#    #+#             */
/*   Updated: 2026/03/13 12:05:36 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_swap_pwd(char *old, char *new, t_env_list *env_list,
		t_data *data)
{
	t_env_list	*cur;

	cur = env_list;
	while (cur)
	{
		if (ft_strcmp(cur->key, "PWD") == 0)
		{
			free(cur->content);
			cur->content = ft_strdup(new);
			if (!cur->content)
				ft_shell_exit(data);
		}
		else if (ft_strcmp(cur->key, "OLDPWD") == 0)
		{
			free(cur->content);
			cur->content = ft_strdup(old);
			if (!cur->content)
				ft_shell_exit(data);
		}
		cur = cur->next;
	}
}

static int	ft_back_home(t_env_list *env_list, char **path, t_data *data)
{
	t_env_list	*cur;
	int			check;

	check = 0;
	cur = env_list;
	if (!*path || !**path || ((ft_strcmp(*path, "~") == 0)))
	{
		while (cur)
		{
			if (ft_strcmp(cur->key, "HOME") == 0)
			{
				if (*path)
					free(*path);
				*path = ft_strdup(cur->content);
				if (!*path)
					ft_shell_exit(data);
				check = 1;
			}
			cur = cur->next;
		}
		if (!check)
			return (0);
	}
	return (1);
}

static int	ft_back_old(t_env_list *env_list, char **path, t_data *data)
{
	t_env_list	*cur;
	int			check;

	check = 0;
	cur = env_list;
	if (*path && ft_strcmp(*path, "-") == 0)
	{
		while (cur)
		{
			if (ft_strcmp(cur->key, "OLDPWD") == 0)
			{
				free(*path);
				*path = ft_strdup(cur->content);
				if (!*path)
					ft_shell_exit(data);
				ft_putstr(*path);
				write(1, "\n", 1);
				check = 1;
			}
			cur = cur->next;
		}
		if (!check)
			return (0);
	}
	return (1);
}

static int	ft_old_home(t_env_list *env_list, char **path, t_data *data)
{
	if (!ft_back_home(env_list, path, data))
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (0);
	}
	if (!ft_back_old(env_list, path, data))
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (0);
	}
	return (1);
}

int	ft_cd(char **path, t_env_list *env_list, t_data *data)
{
	char	*cur_path;

	cur_path = NULL;
	cur_path = getcwd(cur_path, PATH_MAX);
	if (!cur_path)
		perror("getcwd");
	if (!ft_old_home(env_list, path, data))
	{
		if (cur_path)
			free(cur_path);
		g_sig_status = 1;
		return (-1);
	}
	if (chdir(*path) == -1)
	{
		if (cur_path)
			free(cur_path);
		g_sig_status = 1;
		return (perror("chdir"), (-1));
	}
	ft_swap_pwd(cur_path, *path, env_list, data);
	free(*path);
	*path = NULL;
	free(cur_path);
	return (0);
}
