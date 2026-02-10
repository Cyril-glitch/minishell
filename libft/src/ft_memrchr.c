/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:45:38 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 11:54:21 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../inc/libft.h"

void	*ft_memrchr(const void *s, int c, size_t n)
{
	const unsigned char	*source;
	unsigned char		chr;

	chr = c;
	source = s;
	while (n > 0)
	{
		n--;
		if (source[n] == chr)
			return ((void *)(source + n));
	}
	return (NULL);
}
