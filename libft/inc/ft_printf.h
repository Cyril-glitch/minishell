/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:27:46 by cycolonn          #+#    #+#             */
/*   Updated: 2026/02/10 14:43:26 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../inc/libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_flags
{
	int		minus;
	int		zero;
	int		dot;
	int		hash;
	int		space;
	int		plus;
	int		precision;
	int		width;
}			t_flags;

typedef struct s_format
{
	char	*content;
	char	*prefix;
	char	*precise;
	char	*zeropad;
	char	*mid;
}			t_format;

// main function
int			ft_printf(const char *str, ...);

// conversion functions
int			ft_printchar(int c, t_flags *f);
int			ft_printstr(char *s, t_flags *f, t_format *fmt);
int			ft_printnbr(int n, t_flags *f, t_format *fmt);
int			ft_printptr_hex(void *ptr, t_flags *f, t_format *fmt);
int			ft_printunsigned(unsigned int n, t_flags *f, t_format *fmt);
int			ft_printlower_hex(unsigned int n, t_flags *f, t_format *fmt);
int			ft_printupper_hex(unsigned int n, t_flags *f, t_format *fmt);
int			ft_utoabase(unsigned long nbr, const char *base, t_format *fmt);

// ft_flags_utils.c
t_flags		*ft_flaginit(void);
int			ft_enableflags(const char *str, t_flags *f, int *count);
void		ft_normalize(t_flags *f);
void		ft_flagstate(t_flags *f);
void		ft_flagzero(t_flags *f);
int			ft_invalideflags(char end, t_flags *f);

// ft_format_utils.c
int			ft_prefix(long n, char conv, t_flags *f, t_format *fmt);
int			ft_precision_str(t_flags *f, t_format *fmt);
int			ft_precision_nbr(unsigned long n, t_flags *f, t_format *fmt);
int			ft_zero(t_flags *f, t_format *fmt);
int			ft_midcontent(t_format *fmt);
int			ft_padandprint(char *mid, int midlen, t_flags *f);

// format
t_format	*ft_fmtinit(void);
void		ft_freeall(t_format *fmt);

#endif
