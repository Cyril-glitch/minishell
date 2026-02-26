/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:49:44 by cycolonn          #+#    #+#             */
/*   Updated: 2026/02/25 21:03:56 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*d;

	if (size > 0 && nmemb > (size_t)-1 / size)
		return (NULL);
	d = malloc(size * nmemb);
	if (d)
	{
		ft_memset(d, 0, size * nmemb);
		return (d);
	}
	return (NULL);
}
