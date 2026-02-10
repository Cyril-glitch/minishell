/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:07:36 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 12:22:55 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static void	ft_local_disable(t_flags *f)
{
	f->hash = 0;
}

static unsigned long	ft_abs(int n)
{
	unsigned long	abs;
	long			nbr;

	abs = 0;
	nbr = (long)n;
	if (nbr < 0)
		nbr *= -1;
	abs = nbr;
	return (abs);
}

int	ft_printnbr(int n, t_flags *f, t_format *fmt)
{
	int	count;

	ft_local_disable(f);
	if (ft_utoabase(ft_abs(n), "0123456789", fmt) == -1)
		return (-1);
	if (ft_prefix(n, 'd', f, fmt) == -1)
		return (-1);
	if (ft_precision_nbr(n, f, fmt) == -1)
		return (-1);
	if (ft_zero(f, fmt) == -1)
		return (-1);
	if (ft_midcontent(fmt) == -1)
		return (-1);
	count = ft_padandprint(fmt->mid, ft_strlen(fmt->mid), f);
	ft_freeall(fmt);
	return (count);
}
