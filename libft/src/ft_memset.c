/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:09:06 by cycolonn          #+#    #+#             */
/*   Updated: 2026/02/26 09:24:15 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*dst;
	size_t			i;

	i = 0;
	dst = s;
	while (i < n)
		dst[i++] = (unsigned char) c;
	return (dst);
}
