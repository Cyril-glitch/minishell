/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:13:50 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 11:54:21 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;
	char	c;

	nbr = (long)n;
	if (nbr < 0)
	{
		nbr *= -1;
		write(fd, "-", 1);
	}
	if (nbr > 9)
		ft_putnbr_fd(nbr / 10, fd);
	nbr %= 10;
	c = '0' + nbr;
	write(fd, &c, 1);
}
/*
   int main (int ac, char **av)
   {
   if (ac < 2)
   return 0;

   char c;
   c = 0;

   int fd;
   fd = ft_wopen(av[1]);
   ft_putnbr_fd(-2147483647,fd);
   close(fd);

   fd = ft_ropen(av[1]);
   ft_cat(fd,&c);
   close(fd);
   }
   */
