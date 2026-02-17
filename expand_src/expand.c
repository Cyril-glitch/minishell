#include  "../inc/minishell.h"

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
      //printf("quote = %d \n d_quote = %d", data->expd->quote, data->expd->d_quote);
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
