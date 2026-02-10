/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdouble.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 14:05:11 by cycolonn          #+#    #+#             */
/*   Updated: 2026/02/10 14:05:23 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_putdouble(double d, int precision)
{
	long	n;
	long	dec;

	if (d < 0)
	{
		write(1, "-", 1);
		d = -d;
	}
	n = (long)d;
	dec = d - n;
	if (precision <= 0)
	{
		ft_putnbr(n);
		return ;
	}
	while (precision)
	{
		dec *= 10;
		precision--;
	}
	ft_putnbr(n);
	write(1, ".", 1);
	ft_putnbr(dec);
}
