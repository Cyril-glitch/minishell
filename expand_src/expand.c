#include  "../inc/minishell.h"

static size_t  ft_newlen(t_list *expd_lst)
{
  size_t len;
  t_list *current;

  len = 0;
  current = expd_lst;
  while (current)
  {
    len += ft_strlen((char*)current->content);
    current = current->next;
  }
  return len;
}

static void ft_expanded(char *content, t_list *expd_lst, t_data *data)
{
  size_t  len;
  size_t  i;
  size_t  j;
  t_list *current;

  j = 0;
  i = 0;
  len = 0;
  len = ft_newlen(expd_lst);
  current = expd_lst;
  free(content);
  content = malloc(sizeof(char) * (len + 1));
  if (!content)
    ft_shell_exit(data);
  while(current)
  {
    i = 0;
    while(((char*)expd_lst->content)[i])
    {
      content[j] = ((char*)expd_lst->content)[i];
      i++;
      j++;
    }
    content[j] = 0;
    current = current->next;
  }
}

void ft_expand(t_token *token_lst, t_env_list *env_lst, t_data *data)
{
  while (token_lst)
  {
      ft_subtitute(token_lst->content, token_lst, env_lst, data);
      ft_expanded(token_lst->content, data->expd_lst,data);
      token_lst = token_lst->next;
  }
}
