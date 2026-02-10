/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:21:41 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 12:22:55 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

t_flags	*ft_flaginit(void)
{
	t_flags	*f;

	f = malloc(sizeof(t_flags));
	if (!f)
		return (NULL);
	f->minus = 0;
	f->zero = 0;
	f->dot = 0;
	f->hash = 0;
	f->space = 0;
	f->plus = 0;
	f->precision = 0;
	f->width = 0;
	return (f);
}

void	ft_flagzero(t_flags *f)
{
	f->minus = 0;
	f->zero = 0;
	f->dot = 0;
	f->hash = 0;
	f->space = 0;
	f->plus = 0;
	f->precision = 0;
	f->width = 0;
}

static int	ft_width_and_precision(const char *str, t_flags *f)
{
	int	i;

	i = 0;
	if (str[i] >= '1' && str[i] <= '9')
	{
		f->width = ft_atoi(&str[i]);
		while ((str[i] >= '0' && str[i] <= '9'))
			i++;
	}
	if (str[i] == '.')
	{
		f->dot = 1;
		i++;
	}
	if (ft_isdigit(str[i]))
	{
		f->precision = ft_atoi(&str[i]);
		while ((str[i] >= '0' && str[i] <= '9'))
			i++;
	}
	return (i);
}

int	ft_enableflags(const char *str, t_flags *f, int *count)
{
	int	i;

	i = 0;
	while (ft_isset(str[i], "-0# +"))
	{
		f->minus += (str[i] == '-');
		f->zero += (str[i] == '0');
		f->hash += (str[i] == '#');
		f->space += (str[i] == ' ');
		f->plus += (str[i] == '+');
		i++;
	}
	i += ft_width_and_precision(&str[i], f);
	if (ft_isset(str[i], "cspdiuxX%"))
	{
		ft_normalize(f);
		return (i);
	}
	if (str[i] != '%')
		*count += write(1, "%", 1);
	*count += write(1, str, i + 1);
	return (i);
}

void	ft_normalize(t_flags *f)
{
	if (f->minus)
		f->zero = 0;
	if (f->dot)
		f->zero = 0;
	if (f->plus)
		f->space = 0;
	if (f->width < 0)
		f->width *= -1;
	if (f->precision < 0)
		f->precision *= -1;
}
/*
   void	ft_flagstate(t_flags *f)
   {
   printf("\n\n");
   printf("ETAT DES FLAGS\n\n");
   printf("- = %d\n",f->minus);
   printf("0 = %d\n",f->zero);
   printf(". = %d\n",f->dot);
   printf("# = %d\n",f->hash);
   printf("' ' = %d\n",f->space);
   printf("+ = %d\n",f->plus);
   printf("preci = %d\n",f->precision);
   printf("width = %d\n",f->widht);
   printf("\n\n");
   printf("TEST\n\n");
   }
 */
