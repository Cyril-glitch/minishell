/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:05:05 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 11:54:21 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	newlen;
	char	*d;

	d = NULL;
	newlen = 0;
	if (!s1 && !s2)
		return (ft_strdup(""));
	newlen = ft_strlen(s1) + ft_strlen(s2);
	d = malloc(sizeof(char) * (newlen + 1));
	if (!d)
		return (NULL);
	return (ft_strcat(ft_strcpy(d, s1), s2));
}
