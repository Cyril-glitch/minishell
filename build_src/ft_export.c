/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 09:12:28 by mathis            #+#    #+#             */
/*   Updated: 2026/03/10 13:50:46 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_sort(int size, char **tab)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	temp = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
			{
				temp = tab[i];
				tab[i] = tab[j];
				tab[j] = temp;
			}
			j++;
		}
		i++;
	}
}

static char	**ft_tab_list(t_env_list *lst)
{
	t_env_list	*cur;
	char		**tab;
	int			len;

	len = 0;
	cur = lst;
	while (cur)
	{
		len++;
		cur = cur->next;
	}
	tab = malloc(sizeof(char *) * (len + 1));
	if (!tab)
		return (NULL);
	len = 0;
	while (lst)
	{
		tab[len] = ft_strdup((char *)lst->line);
		if (!tab[len])
			return (NULL);
		len++;
		lst = lst->next;
	}
	tab[len] = NULL;
	return (tab);
}

static void	ft_printlst_export(t_env_list *env_list, t_data *data)
{
	char		**tab;
	int			size;
	t_env_list	*dup;

	size = 0;
	tab = ft_tab_list(env_list);
	if (!tab)
		ft_shell_exit(data);
	while (tab[size])
		size++;
	ft_sort(size, tab);
	size = 0;
	while (tab[size])
	{
		ft_putstr("export ");
		dup = ft_key_hunter(tab[size], env_list, data);
		ft_putstr(dup->key);
		if (dup->content)
		{
			ft_putstr("=\"");
			ft_putstr(dup->content);
			ft_putstr("\"");
		}
		write(1, "\n", 1);
		size++;
	}
	ft_tabclear(tab);
}

static int	ft_valid_args(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[i]) && s[i] != '_')
	{
		ft_putstr_fd("losmaquinos: export: \" ", 2);
		write(2, &s[i], 1);
		ft_putstr_fd(" \" : identifiant non valable\n", 2);
		return (0);
	}
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_' && s[i] != '?')
		{
			ft_putstr_fd("losmaquinos: export: \" ", 2);
			ft_putstr_fd(s, 2);
			ft_putstr_fd(" \" : identifiant non valable\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_export(char **args, t_env_list **env_list, t_data *data)
{
	int			i;
	t_env_list	*tmp;
	t_env_list	*dup;

	i = 1;
	tmp = NULL;
	dup = NULL;
	if (!args[i])
	{
		ft_printlst_export(*env_list, data);
		return (0);
	}
	while (args[i])
	{
		if (ft_valid_args(args[i]))
		{
			tmp = ft_new_env(args[i]);
			dup = ft_key_hunter(args[i], *env_list, data);
			if (!tmp)
				ft_shell_exit(data);
			if (dup && ft_strcmp(dup->key, tmp->key) == 0)
				ft_del_env(dup, env_list);
			ft_lstadd_back_env(env_list, tmp);
		}
		i++;
	}
	return (1);
}
