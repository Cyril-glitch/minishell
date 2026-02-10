/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:33:17 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 12:22:55 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static void	ft_nullformat(t_format *fmt)
{
	fmt->content = NULL;
	fmt->prefix = NULL;
	fmt->precise = NULL;
	fmt->zeropad = NULL;
	fmt->mid = NULL;
}

void	ft_freeall(t_format *fmt)
{
	if (fmt->content)
		free(fmt->content);
	if (fmt->prefix)
		free(fmt->prefix);
	if (fmt->precise)
		free(fmt->precise);
	if (fmt->zeropad)
		free(fmt->zeropad);
	if (fmt->mid)
		free(fmt->mid);
	ft_nullformat(fmt);
}
