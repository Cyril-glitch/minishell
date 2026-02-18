/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:08:41 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 11:54:21 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static	int	ft_load(char **tab, char const *s, char *set, int  index)
{
	size_t	len;

	len = 0;


  while (*s && ft_isset(*s, set))
		s++;
  if (!*s)
  {
    tab[index] = NULL;
    return (1);
  }
	while (s[len] && !ft_isset(s[len], set))
		len++;
  tab[index] = malloc(sizeof(char) * (len + 1));
  if (!tab[index])
    return (0);

  ft_strncpy(tab[index], s, len);

  if(ft_load(tab, s + len, set, index + 1))
    return (1);
  free(tab[index]);
  return (0);
}

char	**ft_split_set(char const *s, char *set)
{
	char	**tab;
	int		len;

  if (!s)
    return (NULL);
	len = ft_scountword(s, set);
	tab = malloc(sizeof(char *) * (len + 1));
  if (!tab)
    return (NULL);
	if (ft_load(tab, s, set, 0) == 0)
  {
    free(tab);
    return (NULL);
  }
	return (tab);
}
