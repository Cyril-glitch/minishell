/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:52:09 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 11:54:21 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_numalloc(long *nbr, int *len)
{
	long	tmp;

	*len = (*nbr < 0);
	if (*nbr == 0)
		(*len)++;
	else if (*nbr < 0)
		*nbr *= -1;
	tmp = *nbr;
	while (tmp)
	{
		(*len)++;
		tmp /= 10;
	}
	return (malloc(sizeof(char) * (*len + 1)));
}

char	*ft_itoa(int n)
{
	long		nbr;
	char		*res;
	int			len;

	if (n == 0)
		return (ft_strdup("0"));
	nbr = (long)n;
	len = 0;
	res = ft_numalloc(&nbr, &len);
	if (!res)
		return (NULL);
	res[len] = 0;
	while (nbr)
	{
		res[--len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (n < 0)
		res[0] = '-';
	return (res);
}

/*
   int main()
   {
   char* str = NULL;
   str = ft_itoa(-2147483648);
   printf("%s\n",str);
   }
 */
