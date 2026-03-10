/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 09:12:35 by mathis            #+#    #+#             */
/*   Updated: 2026/03/10 15:16:19 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_color(char *str, char *color)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(color, str);
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, RESET);
	free(tmp);
	return (res);
}

static char	*ft_user(t_env_list *lst)
{
	while (lst)
	{
		if (ft_strcmp("USER", lst->key) == 0)
			return (lst->content);
		lst = lst->next;
	}
	return (NULL);
}

static char	*ft_make_prompt(t_env_list *env_list, t_data *data, char *cur_path)
{
	char	*tmp;
	char	*tmp2;

	ft_free_prompt(data);
	data->prompt->user = ft_color(ft_user(env_list), MINT);
	data->prompt->pwd = ft_color(ft_strrchr(cur_path, '/'), LAVENDER);
	free(cur_path);
	data->prompt->group = ft_strdup(ICE_BLUE "@" RESET B_L_RED \
		"losmachinos🏭" RESET B_BLUE " ~" RESET);
	if (!data->prompt->user || !data->prompt->pwd || !data->prompt->group)
		ft_shell_exit(data);
	tmp = ft_strjoin(data->prompt->user, data->prompt->group);
	if (!tmp)
		ft_shell_exit(data);
	tmp2 = ft_strjoin(tmp, data->prompt->pwd);
	free(tmp);
	if (!tmp2)
		ft_shell_exit(data);
	data->prompt->prompt = ft_strjoin(tmp2, " ");
	free(tmp2);
	if (!data->prompt->prompt)
		ft_shell_exit(data);
	return (data->prompt->prompt);
}

char	*ft_prompt_pwd(t_env_list *env_list, t_data *data)
{
	char	*cur_path;

	cur_path = NULL;
	cur_path = getcwd(cur_path, PATH_MAX);
	if (!cur_path)
	{
		if (data->prompt->prompt)
			free(data->prompt->prompt);
		return (data->prompt->prompt = ft_strdup("@losmachinos🏭:~"));
	}
	else
		return (ft_make_prompt(env_list, data, cur_path));
}

void	ft_pwd(t_env_list *env_list)
{
	char	*cur_path;

	(void)env_list;
	cur_path = NULL;
	cur_path = getcwd(cur_path, PATH_MAX);
	if (!cur_path)
	{
		perror("getcwd");
		return ;
	}
	printf("%s\n", cur_path);
	free(cur_path);
}
