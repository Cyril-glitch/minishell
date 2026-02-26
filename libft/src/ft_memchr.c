/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:36:50 by cycolonn          #+#    #+#             */
/*   Updated: 2026/02/26 09:23:58 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*src;
	unsigned char		chr;
	size_t				i;

	i = 0;
	src = (const unsigned char *)s;
	chr = (unsigned char) c;
	while (i < n)
	{
		if (src[i] == chr)
			return ((void *)(src + i));
		i++;
	}
	return (NULL);
}
