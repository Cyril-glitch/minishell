/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padandprint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:31:52 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 12:22:55 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static int	ft_rightpad(char *mid, int midlen, int pad)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	count += write(1, mid, midlen);
	while (i < pad)
	{
		count += write(1, " ", 1);
		i++;
	}
	return (count);
}

static int	ft_leftpad(char *mid, int midlen, int pad, t_flags *f)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!f->zero)
	{
		while (i < pad)
		{
			count += write(1, " ", 1);
			i++;
		}
	}
	count += write(1, mid, midlen);
	return (count);
}

int	ft_padandprint(char *mid, int midlen, t_flags *f)
{
	int	count;
	int	pad;

	if (!mid)
		return (-1);
	pad = f->width - midlen;
	count = 0;
	if (f->minus)
		count += ft_rightpad(mid, midlen, pad);
	else
		count += ft_leftpad(mid, midlen, pad, f);
	return (count);
}
