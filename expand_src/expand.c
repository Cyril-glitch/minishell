#include  "../inc/minishell.h"

static void	ft_print_lst(t_list	*lst)
{
	t_list	*current = NULL;
	current = lst;

	while(current)
	{
		printf("%s",(char*)current->content);
		current = current->next;
	}
}

void ft_free_cat(t_expand *expd)
{
    if (!expd)
        return ; 
    if (expd->prefix)
        free(expd->prefix);
    if (expd->key)
        free(expd->key);
    if (expd->val)
        free(expd->val);
    if (expd->suffix)
        free(expd->suffix);
}

void    ft_quote_status(t_expand *expd, char c)
{
        if (c == 39 )
        {
            if (expd->quote == 0 && !expd->d_quote)
                expd->quote = 1;
            else if  (expd->quote == 1)
                expd->quote = 0;
        }
        else if (c == 34)
        {
            if (expd->d_quote == 0 && !expd->quote)
                expd->d_quote = 1;
            else if  (expd->d_quote == 1)
                expd->d_quote = 0;
        }
}

void ft_expand(t_token *token_lst, t_env_list *env_lst, t_data *data)
{
  data->expd = malloc(sizeof(t_expand));
  data->expd_lst = malloc(sizeof(t_list));
  if (!data->expd || !data->expd_lst)
      ft_shell_exit(data);
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
