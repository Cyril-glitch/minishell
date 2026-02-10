/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmtinit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:30:45 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 12:22:55 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

t_format	*ft_fmtinit(void)
{
	t_format	*fmt;

	fmt = malloc(sizeof(t_format));
	if (!fmt)
		return (NULL);
	fmt->content = NULL;
	fmt->prefix = NULL;
	fmt->precise = NULL;
	fmt->zeropad = NULL;
	fmt->mid = NULL;
	return (fmt);
}
