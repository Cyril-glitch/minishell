/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:15:36 by mathis            #+#    #+#             */
/*   Updated: 2026/02/19 13:17:51 by mathis           ###   ########.fr       */
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
	if (!env)
		return (NULL);
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	path_str = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
	path_tab = ft_split(path_str, ':');
	return (path_tab);
}

char	*find_way_path(char **path_tab, char *cmd)
{
	int		i;
	char	*way;
	char	*tmp;

	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	if (!path_tab | !cmd)
		return (NULL);
	i = 0;
	while (path_tab[i])
	{
		tmp = ft_strjoin(path_tab[i], "/");
		way = ft_strjoin(tmp, cmd);
		if (!access(way, X_OK))
		{
			free(tmp);
			return (way);
		}
		free(way);
		free(tmp);
		i++;
	}
	return (NULL);
}