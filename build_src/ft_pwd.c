
#include "../inc/minishell.h"

static char *ft_color(char *str, char *color)
{
  char *tmp;
  char *res;

  tmp = ft_strjoin(color, str);
  if (!tmp)
    return NULL;
  res = ft_strjoin(tmp, RESET);
  free(tmp);
  return (res);
}

static char *ft_user(t_env_list *lst)
{
  while (lst)
  {
    if (strcmp("USER", lst->key)== 0)
      return lst->content;
    lst = lst->next;
  }
  return NULL;
}

static char *ft_make_prompt(t_env_list *env_list, t_data *data, char *cur_path)
{
  char *shell;
  char *user;
  char *tmp;
  char *tmp2;
  char *pwd;

  user = ft_color(ft_user(env_list), MINT);
  pwd = ft_color(strrchr(cur_path,'/'), LAVENDER);
  shell = ft_strdup(ICE_BLUE"@"RESET B_L_RED"losmachinos🏭"RESET B_BLUE" ~"RESET);
  if (!shell)
    ft_shell_exit(data);
  tmp = ft_strjoin(user, shell);
  if (!tmp)
    ft_shell_exit(data);
  tmp2 = ft_strjoin(tmp,pwd);
  if (!tmp2)
    ft_shell_exit(data);
  data->prompt = ft_strjoin(tmp2 ," ");
  if (!data->prompt)
    ft_shell_exit(data);
  free(tmp);
  free(tmp2);
  free(shell);
  return data->prompt;
}

char  *ft_prompt_pwd(t_env_list *env_list, t_data *data)
{
  char *cur_path;

  cur_path = NULL;
  cur_path = getcwd(cur_path, PATH_MAX);
  if (!cur_path)
    return (data->prompt = ft_strdup("@losmachinos🏭:~"));
  else
    return (ft_make_prompt(env_list, data, cur_path));
}

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
  printf("%s\n",cur_path);
}
