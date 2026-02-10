/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:17:12 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 12:22:55 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_prefix(long n, char conv, t_flags *f, t_format *fmt)
{
	if (n < 0)
		fmt->prefix = (ft_strdup("-"));
	else if (f->hash && conv == 'x' && n > 0)
		fmt->prefix = (ft_strdup("0x"));
	else if (f->hash && conv == 'X' && n > 0)
		fmt->prefix = (ft_strdup("0X"));
	else if (f->space)
		fmt->prefix = (ft_strdup(" "));
	else if (f->plus)
		fmt->prefix = (ft_strdup("+"));
	else
		fmt->prefix = (ft_strdup(""));
	if (!fmt->prefix)
		return (-1);
	return (0);
}

int	ft_precision_str(t_flags *f, t_format *fmt)
{
	int		len;

	len = ft_strlen(fmt->content);
	if (!f->dot || (f->precision >= len))
	{
		fmt->precise = ft_strdup(fmt->content);
		return (0);
	}
	fmt->precise = malloc(sizeof(char) * (f->precision + 1));
	if (!fmt->precise)
		return (-1);
	ft_bzero(ft_mempcpy(fmt->precise, fmt->content, f->precision), 1);
	return (0);
}

static void	ft_precision_zero(t_flags *f, t_format *fmt)
{
	int	i;
	int	j;
	int	nbrlen;

	i = 0;
	j = 0;
	nbrlen = ft_strlen(fmt->content);
	while (i < (f->precision - nbrlen))
		fmt->precise[i++] = '0';
	while (j < nbrlen)
		fmt->precise[i++] = fmt->content[j++];
	fmt->precise[i] = 0;
}

int	ft_precision_nbr(unsigned long n, t_flags *f, t_format *fmt)
{
	int		len;

	if ((f->dot && f->precision == 0 && n == 0))
	{
		free(fmt->content);
		fmt->content = ft_strdup("");
		if (!fmt->content)
			return (-1);
	}
	len = ft_strlen(fmt->content);
	if (!f->dot || (f->dot && (f->precision <= len)))
	{
		fmt->precise = ft_strdup(fmt->content);
		return (0);
	}
	fmt->precise = malloc(sizeof(char) * (f->precision + 1));
	if (!fmt->precise)
		return (-1);
	ft_precision_zero(f, fmt);
	return (0);
}

int	ft_midcontent(t_format *fmt)
{
	if (fmt->zeropad)
		fmt->mid = ft_strjoin(fmt->prefix, fmt->zeropad);
	else
		fmt->mid = ft_strjoin(fmt->prefix, fmt->precise);
	if (!fmt->mid)
		return (-1);
	return (0);
}
//malloc failtest
/*
   int ft_precision_nbr(unsigned long n, t_flags *f, t_format *fmt)
   {
   int		len;

   if ((f->dot && f->precision == 0 && n == 0))
   {
   free(fmt->content);
   fmt->content = ft_strdup("");
   if (!fmt->content)
   return (-1);
   }
   len = ft_strlen(fmt->content);
   if (!f->dot || (f->dot && (f->precision <= len)))
   {
   fmt->precise = ft_strdup(fmt->content);
   return (0);
   }
   fmt->precise = malloc((size_t)-1);
   if (!fmt->precise)
   return (-1);
   ft_precision_zero(f, fmt);
   return (0);
   }
 */
