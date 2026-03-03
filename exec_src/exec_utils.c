/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtagand <mtagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:15:36 by mathis            #+#    #+#             */
/*   Updated: 2026/03/02 14:36:13 by mtagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_tabclear(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}

char	**parse_path(char **env)
{
	char	**path_tab;
	char	*path_str;
	int		i;

	i = 0;
	if (!env[0])
		return(ft_split("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin", ':'));
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	path_str = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
	if (!path_str)
		return (NULL);
	path_tab = ft_split(path_str, ':');
	free(path_str);
	if (!path_tab)
		return (NULL);
	return (path_tab);
}

char	*shearch_way(char **path_tab, t_data *data, char *cmd)
{
	int		i;
	char	*tmp;
	char	*way;

	i = 0;
	while (path_tab[i])
	{
		tmp = ft_strjoin(path_tab[i], "/");
		if (!tmp)
			ft_shell_exit(data);
		way = ft_strjoin(tmp, cmd);
		if (!way)
		{
			free(tmp);
			ft_shell_exit(data);
		}
		if (!access(way, X_OK))
			return (free(tmp), way);
		free(way);
		free(tmp);
		i++;
	}
	return (NULL);
}

char	*find_way_path(char **path_tab, char *cmd, t_data *data)
{
	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	if (!path_tab | !cmd)
		return (NULL);
	return (shearch_way(path_tab, data, cmd));
	return (NULL);
}
