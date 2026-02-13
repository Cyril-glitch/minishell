#include  "../inc/minishell.h"


int ft_expd_normalise(char c, t_token_list *token_lst )
{
  if (c == '?')
  if (ft_digit(c))
  {
      token_lst->content = ft_strdup("");
  }

  if (c == '?')
  if (c == '?')
  if (c == '?')
  if (c == '?')


}
void ft_subtitute(char *str, t_token_list *token_lst, t_env_list *env_lst)
{
  t_expand expd;

  if (ft_find_env(str))
  {
    while (str != '$')
      i++;
	  expd->prefixe = ft_substr(str, 0, i);
    ft_expd_normalise(str[i]);
    while(ft_isalnum(str[i]) && 
    


  }
}

void ft_expand(t_token_list *token_lst, t_env_list *env_lst)
{
  t_token_list *tmp;

  tmp = NULL;
  while (*token_lst)
  {
      tmp = ft_strchr(token_lst->content,"$");
      if (tmp)
        ft_subtitute(token_lst->content, token_lst, env_lst);
      token_lst = token_lst->next;
  }
}

/*
Cas particuliers à gérer dans ton code :

    $? : S'arrête immédiatement après le ?.

    $1 : creer une chaine vide

    $invalide : pas d'epand
    
    $"" : pas d'expand



    $  (suivi d'un espace) ou $ en fin de ligne : Le $ est traité comme un caractère normal, on ne cherche pas de variable.

*/
