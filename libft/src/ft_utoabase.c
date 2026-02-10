/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:35:13 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 12:22:55 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static int	ft_numalloc(unsigned long nbr, const char *base)
{
	int	i;
	int	baselen;

	i = (nbr == 0);
	baselen = ft_strlen(base);
	while (nbr)
	{
		nbr /= baselen;
		i++;
	}
	return (i);
}

int	ft_utoabase(unsigned long nbr, const char *base, t_format *fmt)
{
	int		baselen;
	int		newlen;

	baselen = ft_strlen(base);
	newlen = ft_numalloc(nbr, base);
	fmt->content = malloc(sizeof(char) * (newlen + 1));
	if (!fmt->content)
		return (-1);
	fmt->content[newlen] = 0;
	while (newlen)
	{
		fmt->content[--newlen] = base[nbr % baselen];
		nbr /= baselen;
	}
	return (0);
}
