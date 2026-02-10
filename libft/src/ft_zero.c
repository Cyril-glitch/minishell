/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zero.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:50:36 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 12:22:55 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_zero(t_flags *f, t_format *fmt)
{
	char	*tmp;
	int		pad;
	int		prelen;

	prelen = 0;
	if (fmt->prefix)
		prelen = ft_strlen(fmt->prefix);
	pad = (f->width - ft_strlen(fmt->precise)) - prelen;
	if (!f->zero || !f->width || pad <= 0)
		return (0);
	tmp = malloc(sizeof(char) * (pad + 1));
	if (!tmp)
		return (-1);
	ft_memset(tmp, '0', pad);
	tmp[pad] = 0;
	fmt->zeropad = ft_strjoin(tmp, fmt->precise);
	free(tmp);
	if (!fmt->zeropad)
		return (-1);
	return (0);
}
