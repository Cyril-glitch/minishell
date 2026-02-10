/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:05:05 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 12:22:55 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../inc/ft_printf.h"

static int	ft_content(char *str, t_format *fmt, t_flags *f)
{
	if (!str)
	{
		if (f->dot && f->precision < 6)
			fmt->content = ft_strdup("");
		else
			fmt->content = ft_strdup("(null)");
	}
	else if (f->dot && f->precision == 0)
		fmt->content = ft_strdup("");
	else
		fmt->content = ft_strdup(str);
	if (!fmt->content)
		return (-1);
	return (0);
}

static void	ft_local_disable(t_flags *f)
{
	f->zero = 0;
	f->hash = 0;
	f->space = 0;
	f->plus = 0;
}

int	ft_printstr(char *str, t_flags *f, t_format *fmt)
{
	int	count;

	count = 0;
	if (str && *str == '\0')
	{
		count = ft_padandprint(str, 0, f);
		ft_freeall(fmt);
		return (count);
	}
	ft_local_disable(f);
	if (ft_content(str, fmt, f) == -1)
		return (-1);
	if (ft_precision_str(f, fmt) == -1)
		return (-1);
	count = ft_padandprint(fmt->precise, ft_strlen(fmt->precise), f);
	ft_freeall(fmt);
	return (count);
}
