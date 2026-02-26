/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:48:01 by cycolonn          #+#    #+#             */
/*   Updated: 2026/02/26 09:24:41 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	char	*p;

	p = NULL;
	p = ft_mempcpy(dst, src, ft_strlen(src));
	*p = '\0';
	return (dst);
}
