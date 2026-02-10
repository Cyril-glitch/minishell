/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:00:48 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 12:22:55 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../inc/ft_printf.h"

static void	ft_local_disable(t_flags *f)
{
	f->zero = 0;
	f->dot = 0;
	f->hash = 0;
	f->space = 0;
	f->plus = 0;
	f->precision = 0;
}

int	ft_printchar(int c, t_flags *f)
{
	int		count;
	char	mid[2];

	mid[0] = (unsigned char)c;
	mid[1] = 0;
	ft_local_disable(f);
	count = ft_padandprint(mid, 1, f);
	return (count);
}
