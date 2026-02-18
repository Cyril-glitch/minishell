/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countword.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:05:09 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 11:54:21 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int ft_countword(const char *s, char c)
{
  int word;

  word = 0;
  while (*s)
  {
    while (*s && *s == c)
      s++;
    if (*s)
      word++;
    while (*s && *s != c)
      s++;
  }
  return (word);
}
