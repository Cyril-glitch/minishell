/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:18:58 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 11:57:13 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	slen;

	slen = ft_strlen(src);
	if (!size)
		return (slen);
	if (slen < size)
		ft_bzero(ft_mempcpy(dst, src, slen), 1);
	else
		ft_bzero(ft_mempcpy(dst, src, size - 1), 1);
	return (slen);
}

/*
   int	main()
   {
   char  dst[100] = "bonjour";
   printf("%d\n",(int)ft_strlcpy(dst,"salut",100));
   printf("%s\n",dst);
   }
 */
