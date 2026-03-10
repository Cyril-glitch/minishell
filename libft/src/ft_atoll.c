/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:03:09 by mathis            #+#    #+#             */
/*   Updated: 2026/03/10 14:13:28 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

long long	ft_atoll(const char *nbr)
{
	int			i;
	int			signe;
	long long	res;

	i = 0;
	signe = 1;
	res = 0;
	while (ft_isspace(nbr[i]))
		i++;
	if (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			signe = -1;
		i++;
	}
	while (ft_isdigit(nbr[i]))
	{
		res *= 10;
		res += nbr[i] - '0';
		i++;
	}
	return (res * signe);
}
