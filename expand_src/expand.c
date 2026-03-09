/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtagand <mtagand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 09:19:40 by mathis            #+#    #+#             */
/*   Updated: 2026/03/03 17:39:15 by mtagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int  ft_no_expand(t_token *token, t_data *data)
{
  char *tmp;

  tmp = NULL;
  if(ft_strcmp(token->content, "\"\"") == 0)
  {
    if(!token->prev || ft_strcmp(token->prev->content, "|") == 0)
    {
      ft_putstr_fd("minishell : command not found", 2);
	    write(1, "\n", 1);
      g_sig_status = 127;
      return (1);
    }
  }
  if (token->prev)
  {
    if(ft_strcmp(token->prev->content, "<<") == 0)
    {
      tmp = ft_delquote(token->content);
      if (!tmp)
        ft_shell_exit(data);
      free(token->content);
      token->content = tmp;
      return (1);
    }
  }
  return (0);
}

static size_t	ft_newlen(t_list *expd_lst)
{
	size_t	len;
	t_list	*current;

	len = 0;
	current = expd_lst;
	while (current)
	{
		len += ft_strlen((char *)current->content);
		current = current->next;
	}
	return (len);
}

static void	ft_expanded(t_token *token, t_list *expd_lst, t_data *data)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*tmp;

	j = 0;
	len = ft_newlen(expd_lst);
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		ft_shell_exit(data);
	while (expd_lst)
	{
		i = 0;
		while (((char *)expd_lst->content)[i])
		{
			tmp[j++] = ((char *)expd_lst->content)[i++];
		}
		tmp[j] = 0;
		expd_lst = expd_lst->next;
	}
	free(token->content);
	token->content = tmp;
}


void	ft_expand(t_token_list *lst, t_env_list *env_lst, t_data *data)
{
	t_token	*current;

	current = lst->head;
	while (current)
	{
        if (!ft_no_expand(current,data))
        {
		    ft_subtitute(current->content, current, env_lst, data);
		    ft_expanded(current, data->expd_lst, data);
		    ft_lstclear(&data->expd_lst, free);
        }
		current = current->next;
	}
    ft_split_expand(lst, data);
}

void ft_expand_line(char **line, t_data *data)
{
    char *tmp;
    t_env_list *dup;

    tmp = *line;
    if(*tmp == '$')
        tmp++;
    else
        return ;
    dup = ft_key_hunter(tmp, data->env_list, data);
    if (!dup)
        return ;
    free(*line);
    *line = ft_strdup(dup->content);
}
