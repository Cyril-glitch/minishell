/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtablen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 12:10:12 by cycolonn          #+#    #+#             */
/*   Updated: 2026/01/21 12:10:16 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_dtablen(void *s)
{
	size_t	i;
	void	**tab;

	i = 0;
	if (!s)
		return (0);
	tab = (void **)s;
	while (tab[i])
		i++;
	return (i);
}
