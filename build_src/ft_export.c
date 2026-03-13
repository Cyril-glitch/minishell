/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 09:12:28 by mathis            #+#    #+#             */
/*   Updated: 2026/03/12 15:54:51 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	int			len;
	t_env_list	*dup;

	tab = ft_tab_list(env_list);
	if (!tab)
		ft_shell_exit(data);
	len = ft_tablen(tab);
	ft_sort(len, tab);
	len = 0;
	while (tab[len])
	{
		ft_putstr("export ");
		dup = ft_key_hunter(tab[len], env_list, data);
		ft_putstr(dup->key);
		if (dup->content)
		{
			ft_putstr("=\"");
			ft_putstr(dup->content);
			ft_putstr("\"");
		}
		write(1, "\n", 1);
		len++;
	}
	ft_tabclear(tab);
}

static int	ft_valid_args(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[i]) && s[i] != '_')
	{
		ft_putstr_fd("losmaquinos: export: `", 2);
		write(2, &s[i], 1);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_sig_status = 1;
		return (0);
	}
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_' && s[i] != '?')
		{
			ft_putstr_fd("losmaquinos: export: `", 2);
			ft_putstr_fd(s, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_sig_status = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

static void	ft_add_export(char *args, t_env_list **env_list, t_data *data)
{
	t_env_list	*tmp;
	t_env_list	*dup;

	if (!ft_valid_args(args))
		return ;
	tmp = ft_new_env(args);
	if (!tmp)
		ft_shell_exit(data);
	dup = ft_key_hunter(args, *env_list, data);
	if (dup)
	{
		if (ft_strcmp(dup->key, tmp->key) == 0 && tmp->content)
		{
			ft_del_env(dup, env_list);
			ft_lstadd_back_env(env_list, tmp);
		}
		else
			ft_clear_node_env(tmp);
	}
	else
		ft_lstadd_back_env(env_list, tmp);
	if (!ft_strcmp(args, "PATH"))
		data->unset = 0;
}

int	ft_export(char **args, t_env_list **env_list, t_data *data)
{
	int	i;

	i = 1;
	if (!args[i])
		return (ft_printlst_export(*env_list, data), 0);
	while (args[i])
		ft_add_export(args[i++], env_list, data);
	return (1);
}
