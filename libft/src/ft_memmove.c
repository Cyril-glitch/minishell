/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:14:39 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 11:57:53 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;

	d = dest;
	s = src;
	if (d == s)
		return (dest);
	else if (d < s)
		ft_memcpy(dest, src, n);
	else
	{
		while (n)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
	}
	return (dest);
}
