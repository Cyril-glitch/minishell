/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:08:41 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 11:54:21 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static	int	ft_parser(char **dst, char const *s, char set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] && ft_ischarset(s[i], set))
		i++;
	while (s[i + j] && !ft_ischarset(s[i + j], set))
		j++;
	if (!j)
		return (0);
	*dst = malloc(sizeof(char) * (j + 1));
	if (!*dst)
		return (-1);
	ft_bzero(ft_mempcpy(*dst, &s[i], j), 1);
	return (i + j);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		n;
	int		res;
	int		i;

	i = 0;
	res = 0;
	n = ft_countword(s, c);
	tab = malloc(sizeof(char *) * (n + 1));
	if (!tab)
		return (NULL);
	while (i < n)
	{
		res = ft_parser(&tab[i], s += res, c);
		if (res == -1)
		{
			ft_freeiter(tab, i);
			return (NULL);
		}
		i++;
	}
	tab[n] = NULL;
	return (tab);
}

/*
int main()
{
	int i = 0;
	char  **tab = NULL;

	tab = ft_split("^^^1^^2a,^^^^3^^^^--h^^^^", '^');
	while (i < 4)
	{
		printf("tab[%d] = %s \n",i,tab[i]);
		i++;
	}
	ft_freeiter(tab,i);
	tab = NULL;
}
*/
