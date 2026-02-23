#include "../inc/minishell.h"

static  void  ft_printenv(t_env_list *lst)
{
  while (lst)
  {
    if (lst->content)
    {
      ft_putstr(lst->line);
      write(1, "\n", 1);
    }
    lst = lst->next;
  }
}

void  ft_env(char **args, t_env_list *env_list)
{
    int			i;

    i = 1;
    if (args[i])
    {
        ft_putstr_fd("losmaquinos: env: identifiant non valable\n", 2);
        return ;
    }
    ft_printenv(env_list);
}
