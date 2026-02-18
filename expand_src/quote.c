#include  "../inc/minishell.h"

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

static int  ft_quotelen(t_expand *expd, char *s)
{
  int i;
  int len;

  i = 0;
  len = 0;
  while(s[i])
  {
    ft_quote_status(expd, s[i]);
    if (s[i] != '\"' && s[i] != '\'')
      len++;
    else if (s[i] == '\"' && expd->quote)
      len++;
    else if (s[i] == '\'' && expd->d_quote)
      len++;
    i++;
  }
  return len;
}

static char *ft_supquote(t_expand *expd, char *s, int len, t_data *data)
{
  int i;
  int j;
  char *tmp;


  i = 0;
  j = 0;
  tmp = 0;
  tmp = malloc(sizeof(char) * (len + 1));
  if (!tmp)
    ft_shell_exit(data);
  while(s[i])
  {
    ft_quote_status(expd, s[i]);
    if (s[i] != '\"' && s[i] != '\'')
      tmp[j++] = s[i];
    else if (s[i] == '\"' && expd->quote)
      tmp[j++] = s[i];
    else if (s[i] == '\'' && expd->d_quote)
      tmp[j++] = s[i];
    i++;
  }
  return tmp;
}

void ft_delquote(t_expand *expd, t_data *data)
{
  int len;

  len = ft_quotelen(expd, expd->cat);
  if (len)
  {
    free(expd->cat);
    expd->cat = ft_supquote(expd, expd->cat, len, data);
  }
}
