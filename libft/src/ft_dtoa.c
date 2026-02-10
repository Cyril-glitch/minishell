/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:46:41 by cycolonn          #+#    #+#             */
/*   Updated: 2026/02/10 12:47:08 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static char	*ft_zero(int zero)
{
	char	*z;
	int		i;

	i = 0;
	if (zero)
		z = malloc(sizeof(char) * (zero + 1));
	else
		return (NULL);
	while (zero)
	{
		z[i] = '0';
		zero--;
		i++;
	}
	z[i] = 0;
	return (z);
}

static char	*ft_result(long dec, long n, char *zero, int minus)
{
	char	*s[6];
	int		i;

	i = 0;
	s[0] = ft_itoa(n);
	s[1] = ft_itoa(dec);
	s[2] = ft_strjoin(s[0], ".");
	s[3] = ft_strjoin(s[2], zero);
	s[4] = ft_strjoin(s[3], s[1]);
	if (zero)
		free(zero);
	if (minus)
		s[5] = ft_strjoin("-", s[4]);
	while (i < 4)
	{
		if (s[i])
			free(s[i++]);
	}
	if (minus)
	{
		if (s[4])
			free(s[4]);
		return (s[5]);
	}
	return (s[4]);
}

char	*ft_dtoa(double d, int precision)
{
	long	n;
	double	dec;
	int		zero;
	int		minus;

	zero = 0;
	minus = 0;
	if (d < 0)
	{
		d = -d;
		minus = 1;
	}
	n = (long)d;
	dec = d - (long)d;
	while (precision > 0)
	{
		dec *= 10;
		precision--;
		if ((long)dec == 0)
			zero++;
	}
	dec += 0.5;
	return (ft_result((long)dec, n, ft_zero(zero), minus));
}
