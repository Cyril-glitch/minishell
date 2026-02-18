#include "../inc/libft.h"

int  ft_strlens(char **tab)
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

