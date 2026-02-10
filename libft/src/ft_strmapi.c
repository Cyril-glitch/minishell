/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:20:41 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 11:54:21 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../inc/libft.h"
/*
   char	toupperf(unsigned int i, char c)
   {
   if(i % 2 == 0)
   c -= 32;

   return c;
   }
 */

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dst;
	unsigned int	i;

	i = 0;
	dst = ft_strdup((char *)s);
	if (!dst)
		return (NULL);
	while (dst[i])
	{
		dst[i] = f(i, dst[i]);
		i++;
	}
	return (dst);
}

/*
   int main()
   {
   printf("%s\n",ft_strmapi("bonjour",toupperf));
   }
 */
