#include "../inc/minishell.h"

static  int  ft_check_home(t_env_list *env_list)
{
  t_env_list *cur;

  cur = env_list;
  while (cur)
  {
    if (ft_strcmp(cur->key, "HOME") == 0)
      return 1;
    cur = cur->next;
  }
  return 0;
}

static  void ft_swap_pwd(char *old, char *new, t_env_list *env_list, t_data *data)
{
  t_env_list *cur;
  int check;

  check = 0;
  cur = env_list;
  while (cur)
  {
    if (ft_strcmp(cur->key, "PWD") == 0)
    {
      free(cur->content);
      cur->content = ft_strdup(new);
      if (!cur->content)
        ft_shell_exit(data);
      check++;
    }
    else if (ft_strcmp(cur->key, "OLDPWD") == 0)
    {
      free(cur->content);
      cur->content = ft_strdup(old);
      if (!cur->content)
        ft_shell_exit(data);
      check++;
    }
    cur = cur->next;
    if (check == 2)
      return ;
  }
}

static  void ft_back_home(t_env_list *env_list, char **path, t_data *data)
{
  t_env_list *cur;

  cur = env_list;
  if (**path == 0 || ((ft_strcmp(*path, "--") == 0)))
  {
    while (cur)
    {
      if (ft_strcmp(cur->key, "HOME") == 0)
      {
        *path = ft_strdup(cur->content);
        if (!*path)
          ft_shell_exit(data);
      }
      cur = cur->next;
    }
  }
}

static  void ft_back_old(t_env_list *env_list, char **path, t_data *data)
{
  t_env_list *cur;
  int check;

  check = 0;
  cur = env_list;
  if (**path == '-')
  {
    while (cur)
    {
      if (ft_strcmp(cur->key, "OLDPWD") == 0)
      {
        *path = ft_strdup(cur->content);
        if (!*path)
          ft_shell_exit(data);
        check = 1;
      }
      cur = cur->next;
    }
    if (!check)
        ft_putstr_fd("cd: OLDPWD not set\n", 2);
  }
}

int  ft_cd(char *path,t_env_list *env_list, t_data *data)
{
  char *cur_path;

  cur_path = NULL;
  if (!ft_check_home(env_list))
    return (ft_putstr_fd("cd: HOME not set\n", 2),(-1));
  cur_path = getcwd(cur_path, PATH_MAX);
  if (!cur_path)
    return (perror("getcwd"),(-1));
  ft_back_home(env_list, &path, data);
  ft_back_old(env_list, &path, data);
  if (chdir(path) == -1)
    return (perror("chdir"),(-1));
  ft_swap_pwd(cur_path,path, env_list, data);
  return (0);
}

