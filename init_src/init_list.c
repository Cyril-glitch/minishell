#include "../inc/minishell.h"

void  ft_add_expand(t_data *data)
{
  data->expd = malloc(sizeof(t_expand));
  data->expd->prefix = NULL;
  data->expd->key = NULL;
  data->expd->val = NULL;
  data->expd->suffix = NULL;
  data->expd->cat = NULL;  

  data->expd->quote = 0;
  data->expd->d_quote = 0;
}

void    ft_add_env_list(t_data *data, char **env)
{
  t_env_list  *env_list;

  env_list = ft_env_list(env);
  data->env_list = env_list;
}

void    ft_add_token_list(t_data *data)
{
    data->token_list = malloc(sizeof(t_token_list));
    if (!data->token_list)
      ft_shell_exit(data);
}


