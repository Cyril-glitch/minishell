/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:58:10 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 11:54:21 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*d;
	size_t	slen;
	size_t	mlen;

	if (!s || !len)
		return (ft_strdup(""));
	d = NULL;
	mlen = 0;
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len <= slen - start)
		mlen = len;
	else
		mlen = slen - start;
	d = malloc(sizeof(char) * (mlen + 1));
	if (!d)
		return (NULL);
	ft_bzero(ft_mempcpy(d, s + start, mlen), 1);
	return (d);
}
/*
   int main()
   {
   printf("%s\n",ft_substr("",0,0));
   }
 */
