#include  "./inc/minishell.h"

volatile  sig_atomic_t g_sig_status;

int main(int ac, char **av, char **env)
{
    t_data *data;
    data = ft_init_data(ac,av,env);

  while(1)
  {
    data->line = readline("losmachinos:~$ ");
    if (!data->line)
      ft_shell_exit(data);
    add_history(data->line);
    lexer(data->line, data->token_list);
    printf("\n\n\n");
    printf("ETAT DU LEXER AVANT EXPAND :\n\n");
    ft_display_list(data->token_list);
    printf("\n\n\n");
    ft_expand(data->token_list->head, data->env_list,data);
    printf("\n\n\n");
    printf("ETAT DU LEXER APRES EXPAND :\n\n");
    ft_display_list(data->token_list);
    printf("\n\n\n");
    ft_db_lstclear(data->token_list, free);
    free(data->line);
  }
}
