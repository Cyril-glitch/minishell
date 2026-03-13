/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtitute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 12:09:50 by cycolonn          #+#    #+#             */
/*   Updated: 2026/03/13 12:09:52 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_prefix(char *str, t_expand *expd, t_data *data)
{
	int	i;

	i = 0;
	while (str[i] != '$' && str[i])
	{
		ft_quote_status(expd, str[i]);
		i++;
	}
	expd->prefix = ft_substr(str, 0, i);
	if (!expd->prefix)
		ft_shell_exit(data);
	return (i);
}

static char	*ft_expansion(char *key, t_env_list *env_lst, t_data *data)
{
	char	*tmp;

	tmp = NULL;
	if (data->expd->quote == '\'')
	{
		tmp = ft_strjoin("$", key);
		if (!tmp)
			ft_shell_exit(data);
		return (tmp);
	}
	while (env_lst)
	{
		if (ft_strcmp(key, env_lst->key) == 0)
		{
			tmp = ft_strdup(env_lst->content);
			if (!tmp)
				ft_shell_exit(data);
			return (tmp);
		}
		env_lst = env_lst->next;
	}
	return (ft_strdup(""));
}

static int	ft_val(char *str, t_expand *expd, t_env_list *env_lst, t_data *data)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	res = ft_val_edge_case(str, expd, data);
	if (res != -1)
		return (res);
	i++;
	while ((ft_isalnum(str[i]) && str[i] != '\'' && str[i] != '\"')
		|| str[i] == '_')
		i++;
	expd->key = ft_substr(str, 1, (i - 1));
	if (!expd->key)
		ft_shell_exit(data);
	expd->val = ft_expansion(expd->key, env_lst, data);
	if (!expd->val)
		ft_shell_exit(data);
	return (i);
}

static int	ft_cat(char *str, t_expand *expd, t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i] && str[i] != '$')
	{
		ft_quote_status(expd, str[i]);
		i++;
	}
	expd->suffix = ft_substr(str, 0, i);
	tmp = ft_strjoin(expd->prefix, expd->val);
	if (!tmp || !expd->suffix)
		ft_shell_exit(data);
	expd->cat = ft_strjoin(tmp, expd->suffix);
	free(tmp);
	return (i);
}

void	ft_subtitute(char *str, t_token *token_lst, t_env_list *env_lst,
		t_data *data)
{
	t_list	*new;

	new = NULL;
	str += ft_prefix(str, data->expd, data);
	str += ft_val(str, data->expd, data->env_list, data);
	str += ft_cat(str, data->expd, data);
	new = ft_lstnew(ft_strdup(data->expd->cat));
	if (!new)
		ft_shell_exit(data);
	ft_lstadd_back(&data->expd_lst, new);
	ft_expd_zero(data->expd);
	if (*str)
		ft_subtitute(str, token_lst, env_lst, data);
}
