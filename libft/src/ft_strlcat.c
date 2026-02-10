/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:26:57 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 11:54:21 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	size_t	dlen;
	size_t	slen;
	size_t	tlen;
	char	*d;

	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	tlen = dlen + slen;
	d = dst + dlen;
	if (dsize <= dlen)
		return (dsize + slen);
	if (tlen < dsize)
		ft_memset(ft_mempcpy(d, src, slen), 0, 1);
	else
		ft_memset(ft_mempcpy(d, src, (dsize - dlen) - 1), 0, 1);
	return (tlen);
}
