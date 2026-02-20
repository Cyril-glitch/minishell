
#include "../inc/minishell.h"

void  ft_pwd(t_env_list *env_list)
{
  (void)env_list;
  char *cur_path;

  cur_path = NULL;
  cur_path = getcwd(cur_path, PATH_MAX);
  if (!cur_path)
  {
    perror("getcwd");
    return ;
  }
  printf("PWD = %s\n",cur_path);
}
