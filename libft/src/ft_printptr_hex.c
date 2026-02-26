/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr_hex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:10:13 by cycolonn          #+#    #+#             */
/*   Updated: 2026/02/26 09:22:06 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static void	ft_localdisable(t_flags *f)
{
	f->zero = 0;
	f->dot = 0;
	f->hash = 0;
	f->space = 0;
	f->plus = 0;
	f->precision = 0;
}

int	ft_printptr_hex(void *ptr, t_flags *f, t_format *fmt)
{
	unsigned long	uptr;
	int				count;

	if (!ptr)
	{
		fmt->content = ft_strdup("(nil)");
		if (!fmt->content)
			return (-1);
		count = ft_padandprint(fmt->content, ft_strlen(fmt->content), f);
		ft_freeall(fmt);
		return (count);
	}
	ft_localdisable(f);
	uptr = (unsigned long)ptr;
	if (ft_utoabase(uptr, "0123456789abcdef", fmt) == -1)
		return (-1);
	fmt->prefix = ft_strdup("0x");
	fmt->precise = ft_strdup(fmt->content);
	if (!fmt->prefix || !fmt->precise)
		return (-1);
	if (ft_midcontent(fmt) == -1)
		return (-1);
	count = ft_padandprint(fmt->mid, ft_strlen(fmt->mid), f);
	ft_freeall(fmt);
	return (count);
}
