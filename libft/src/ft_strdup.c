/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:54:17 by cycolonn          #+#    #+#             */
/*   Updated: 2026/02/25 21:04:06 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strdup(const char *s)
{
	char	*d;

	d = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!d)
		return (NULL);
	return (ft_strcpy(d, s));
}
