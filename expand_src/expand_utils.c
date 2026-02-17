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

static int  ft_strlens(char **tab)
{
  int len;
  int i;

  len = 0;
  i = 0;
  while(tab[i])
  {
    len += ft_strlen(tab[i]);
    i++;
  }
  return len;
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
  if (expd->quote)
    tab = ft_split(expd->cat, 39);
  else if (expd->d_quote)
    tab = ft_split(expd->cat, 34);
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
