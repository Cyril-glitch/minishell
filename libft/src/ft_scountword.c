
#include "../inc/libft.h"

int ft_scountword(const char *s, char *set)
{
  int word;

  word = 0;
  while (*s)
  {
    while (*s && ft_isset(*s, set))
      s++;
    if (*s)
      word++;
    while (*s && !ft_isset(*s, set))
      s++;
  }
  return (word);
}


