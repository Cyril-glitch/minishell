/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:12:00 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 12:22:55 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../inc/ft_printf.h"

static void	ft_local_disable(t_flags *f)
{
	f->hash = 0;
	f->space = 0;
	f->plus = 0;
}

int	ft_printunsigned(unsigned int n, t_flags *f, t_format *fmt)
{
	int	count;

	ft_local_disable(f);
	if (ft_utoabase((unsigned long)n, "0123456789", fmt) == -1)
		return (-1);
	if (ft_precision_nbr(n, f, fmt) == -1)
		return (-1);
	if (ft_zero(f, fmt) == -1)
		return (-1);
	if (fmt->zeropad)
		count = ft_padandprint(fmt->zeropad, ft_strlen(fmt->zeropad), f);
	else
		count = ft_padandprint(fmt->precise, ft_strlen(fmt->precise), f);
	ft_freeall(fmt);
	return (count);
}
