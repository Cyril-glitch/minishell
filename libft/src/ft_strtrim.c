/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:01:26 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 11:54:21 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	char	*new;

	if (!s1)
		return (ft_strdup(""));
	i = 0;
	len = ft_strlen(s1);
	new = NULL;
	while (s1[i] && ft_isset(s1[i], set))
		i++;
	while (s1[len - 1] && ft_isset(s1[len - 1], set))
		len--;
	if (!len)
		return (ft_strdup(""));
	new = malloc(sizeof(char) * ((len - i) + 1));
	if (!new)
		return (NULL);
	ft_bzero(ft_mempcpy(new, &s1[i], (len - i)), 1);
	return (new);
}
/*
   int main ()
   {
   char *res = NULL;
   res = ft_strtrim("+++++bonjour+++++++","+");

   printf("res = %s",res);
   }
 */
