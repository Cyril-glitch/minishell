#include  "../inc/minishell.h"

void ft_expd_zero(t_expand *expd)
{
    if (!expd)
        return ;
    if (expd->prefix)
    {
        free(expd->prefix);
        expd->prefix = NULL;
    }
    if (expd->key)
    {
        free(expd->key);
        expd->key = NULL;
    }
    if (expd->val)
    {
        free(expd->val);
        expd->val = NULL;
    }
    if (expd->suffix)
    {
        free(expd->suffix);
        expd->suffix = NULL;
    }
    expd->quote = 0;
    expd->d_quote = 0;
}

static void	ft_print_lst(t_list	*lst)
{
	t_list	*current = NULL;
	current = lst;

	while(current)
	{
		printf("%s\n",(char*)current->content);
		current = current->next;
	}
}

void ft_expand(t_token *token_lst, t_env_list *env_lst, t_data *data)
{
  while (token_lst)
  { 
      ft_subtitute(token_lst->content, token_lst, env_lst, data);
      ft_print_lst(data->expd_lst);
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
