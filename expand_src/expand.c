#include  "../inc/minishell.h"

/*
void    ft_quote(t_expand *expd, char c)
{
        if (c == ''')
        {
            if (expd->quote == 0 && !expd->d_quote)
                expd->quote = 1;
            else if  (expd->quote == 1)
                expd->quote = 0;
        }
        esle if (c == '"')
        {
            if (expd->d_quote == 0 && !expd.quote)
                expd->d_quote = 1;
            else if  (expd.d_quote == 1)
                expd->d_quote = 0;
        }
}

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

    while(str[i])
    {
        ft_quote(expd, str[i]);
        if (str[i] == '$')
        {
            i++;
            if (ft_expd_normalise(str[i], token_lst) == 0)
            {
                while (ft_isalnum(str[i]))
                    i
            }
        }
        else
        {
        }
    }
}

void ft_expand(t_token_list *token_lst, t_env_list *env_lst)
{
  char *tmp;

  tmp = NULL;
  while (*token_lst)
  {
      tmp = ft_strchr(token_lst->content,"$");
      if (tmp)
        ft_subtitute(token_lst->content, token_lst, env_lst);
      token_lst = token_lst->next;
  }
}
*/

/*
Cas particuliers à gérer dans ton code :

    $? : S'arrête immédiatement après le ?.

    $1 : creer une chaine vide

    $invalide : pas d'epand
    
    $"" : pas d'expand



    $  (suivi d'un espace) ou $ en fin de ligne : Le $ est traité comme un caractère normal, on ne cherche pas de variable.

*/
