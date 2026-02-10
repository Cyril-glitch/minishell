/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printupper_hex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:14:59 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 12:22:55 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static void	ft_local_disable(t_flags *f)
{
	f->space = 0;
	f->plus = 0;
}

int	ft_printupper_hex(unsigned int n, t_flags *f, t_format *fmt)
{
	int	count;

	ft_local_disable(f);
	if (ft_utoabase((unsigned long)n, "0123456789ABCDEF", fmt) == -1)
		return (-1);
	if (ft_prefix(n, 'X', f, fmt) == -1)
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
