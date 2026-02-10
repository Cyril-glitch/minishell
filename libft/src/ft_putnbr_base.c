/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:43:52 by cycolonn          #+#    #+#             */
/*   Updated: 2025/07/11 13:28:13 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	invalid(char *base)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (base[i])
	{
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
			{
				return (1);
			}
		j++;
		}
	i++;
	}
	if (i < 2)
	{
		return (1);
	}
	return (0);
}

int	operator(char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
		{
			return (1);
		}
	i++;
	}
	return (0);
}

void	ft_putnbr_base(int nbr, char *base)
{
	int		i;
	long	n;

	i = 0;
	n = (long)nbr;
	if (invalid(base) || operator(base))
	{
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
	}
	while (base[i])
	{
		i++;
	}
	if (n > i - 1)
	{
		ft_putnbr_base(n / i, base);
	}
	n %= i;
	write(1, &base[n], 1);
}
/*
int	main()
{
	ft_putnbr_base(15,"0123456789ABCDEF");
}
*/
