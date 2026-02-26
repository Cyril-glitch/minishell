/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:25:26 by cycolonn          #+#    #+#             */
/*   Updated: 2026/02/25 21:04:24 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t dsize)
{
	size_t	slen;

	slen = ft_strlen(src);
	if (slen <= dsize)
	{
		dst = ft_mempcpy(dst, src, slen);
		ft_memset(dst, '\0', dsize - slen);
	}
	else
	{
		dst = ft_mempcpy(dst, src, dsize);
	}
	return (dst - dsize);
}
