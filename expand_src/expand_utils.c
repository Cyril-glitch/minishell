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

void    ft_quote_status(t_expand *expd, char c)
{
        if (c == '\'' )
        {
            if (expd->quote == 0 && expd->d_quote == 0)
                expd->quote = 1;
            else if(expd->quote == 1 && expd->d_quote == 0)
              expd->quote = 0;
        }
        else if (c == '\"')
        {
            if (expd->d_quote == 0 && expd->quote ==0)
                expd->d_quote = 1;
            else if(expd->d_quote == 1 && expd->quote == 0)
              expd->d_quote = 0;
        }
}

static void ft_jointab(char **tab, char *str)
{
  int i;
  int j;
  int k;

  i = 0;
  j = 0;
  k = 0;
  while(tab[i])
  {
    //printf("tab[%d] = %s\n", i,tab[i]);
    j = 0;
    while(tab[i][j])
    {
      str[k] = tab[i][j];
      k++;
      j++;
    }
    i++;
  }
  str[k] = 0;
}

void  ft_delquote(t_expand *expd, t_data *data)
{
  int len;
  char **tab;

  len = 0;
  tab = NULL;
  printf("quote = %d \n d_quote = %d\n", data->expd->quote, data->expd->d_quote);
  if (expd->quote)
    tab = ft_split(expd->cat, '\'');
  else if (expd->d_quote)
    tab = ft_split_set(expd->cat, '\"');
  else
    return ;
  if (!tab)
    ft_shell_exit(data);
  ft_strlens(tab);
  free(expd->cat);
  expd->cat = malloc(sizeof(len + 1));
  if (!expd->cat)
    ft_shell_exit(data);
  ft_jointab(tab, expd->cat);
}
