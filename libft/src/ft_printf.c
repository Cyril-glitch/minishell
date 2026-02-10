/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:26:03 by cycolonn          #+#    #+#             */
/*   Updated: 2026/01/21 12:18:24 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static int	ft_printconv(char conv, t_flags *f, t_format *fmt, va_list args)
{
	int	count;

	count = 0;
	if (conv == 'c')
		count = ft_printchar(va_arg(args, int), f);
	else if (conv == 's')
		count = ft_printstr(va_arg(args, char *), f, fmt);
	else if (conv == 'p')
		count = ft_printptr_hex(va_arg(args, void *), f, fmt);
	else if (conv == 'd' || conv == 'i')
		count = ft_printnbr(va_arg(args, int), f, fmt);
	else if (conv == 'u')
		count = ft_printunsigned(va_arg(args, unsigned int), f, fmt);
	else if (conv == 'x')
		count = ft_printlower_hex(va_arg(args, unsigned int), f, fmt);
	else if (conv == 'X')
		count = ft_printupper_hex(va_arg(args, unsigned int), f, fmt);
	else if (conv == '%')
		count = write(1, "%", 1);
	ft_freeall(fmt);
	ft_flagzero(f);
	return (count);
}

static int	ft_printer(const char *str, va_list args, t_flags *f, t_format *fmt)
{
	int	count;
	int	shield;
	int	i;

	count = 0;
	shield = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			i += ft_enableflags(&str[i], f, &count);
			shield = ft_printconv(str[i], f, fmt, args);
			if (shield == -1)
				return (-1);
			count += shield;
		}
		else
			count += write(1, &str[i], 1);
		i++;
	}
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list		args;
	int			count;
	t_flags		*f;
	t_format	*fmt;

	f = ft_flaginit();
	if (!f)
		return (-1);
	fmt = ft_fmtinit();
	if (!fmt)
		return (-1);
	count = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	count = ft_printer(str, args, f, fmt);
	va_end(args);
	free(f);
	free(fmt);
	return (count);
}

/*
   int main()
   {
   int resft = 0;
   int res = 0;

//test %c
char			c = 'a';
resft = ft_printf("test 'c' = %c\n",c);
res = printf("test 'c' = %c\n",c);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
write(1, "\n\n", 2);

//test %s
char			*s = "bonjour";
resft = ft_printf("test 's' = %s\n",s);
res = printf("test 's' = %s\n",s);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
write(1, "\n\n", 2);

//test %p
char			*p = "test" ;
resft = ft_printf("test 'p' sur l'adresse = %p\n",p);
res = printf("test 'p' sur l'adresse = %p\n",p);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
write(1, "\n\n", 2);

//test %d
int				d = -2147483648;
resft = ft_printf("test 'd' = %d\n",d);
res = printf("test 'd' = %i\n",d);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
write(1, "\n\n", 2);

//test %i
int				i = -2147483648;
resft = ft_printf("test 'i' = %i\n",i);
res = printf("test 'i' = %i\n",i);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
write(1, "\n\n", 2);


//test %u
unsigned int	u = 4000000000;
resft = ft_printf("test 'u' = %u\n",u);
res = printf("test 'u' = %u\n",u);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
write(1, "\n\n", 2);

//test %x
int				x = -657435;
resft = ft_printf("test 'x' = %x\n",x);
res = printf("test 'x' = %x\n",x);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
write(1, "\n\n", 2);

//test %X
int				X = -657435;
resft = ft_printf("test 'X' = %X\n",X);
res = printf("test 'X' = %X\n",X);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
write(1, "\n\n", 2);
}
*/

/*
   int main()
   {
   int resft = 0;
   int res = 0;

   ft_printf("TEST VAL NULL\n\n");

   char  c = 0;
   resft = ft_printf("test 'c' = %c\n",c);
   res = printf("test 'c' = %c\n",c);
   printf("resft = %d\n",resft);
   printf("res = %d\n",res);
   write(1, "\n\n", 2);

//test %s
char			*s = 0;
resft = ft_printf("test 's' = %s\n",s);
res = printf("test 's' = %s\n",s);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
write(1, "\n\n", 2);

//test %p
char			*p = 0;
resft = ft_printf("test 'p' sur l'adresse = %p\n",p);
res = printf("test 'p' sur l'adresse = %p\n",p);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
write(1, "\n\n", 2);

//test %d
int				d = 0;
resft = ft_printf("test 'd' = %d\n",d);
res = printf("test 'd' = %i\n",d);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
write(1, "\n\n", 2);

//test %i
int				i = 0;
resft = ft_printf("test 'i' = %i\n",i);
res = printf("test 'i' = %i\n",i);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
write(1, "\n\n", 2);


//test %u
unsigned int	u = 0;
resft = ft_printf("test 'u' = %u\n",u);
res = printf("test 'u' = %u\n",u);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
write(1, "\n\n", 2);

//test %x
int				x = 0;
resft = ft_printf("test 'x' = %x\n",x);
res = printf("test 'x' = %x\n",x);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
write(1, "\n\n", 2);

//test %X
int				X = 0;
resft = ft_printf("test 'X' = %X\n",X);
res = printf("test 'X' = %X\n",X);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
write(1, "\n\n", 2);
}
*/
/*
   int main()
   {
   int resft = 0;
   int res = 0;

//test %c
//flag autorise - et widht
int				c = 'a';
resft = ft_printf("test %%c = |%-20c|\n",c);
res = printf("test %%c = |%-20c|\n",c);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
printf("\n\n");

//test forbiden
resft = ft_printf("test %%c = |%+0.20c|\n",c);
res = printf("test %%c = |%+0.20c|\n",c);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
printf("\n\n");

//test %s
//flags autorise - et .
char			*s = "hello";
resft = ft_printf("test %%s = |%-.3s|\n",s);
res = printf("test %%s = |%-.3s|\n",s);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
printf("\n\n");

//test vide si precision 0
resft = ft_printf("test %%s = |%-05.s|\n",s);
res = printf("test %%s = |%-05.s|\n",s);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
printf("\n\n");

//test NULL + precision > len
s = NULL;
resft = ft_printf("testp %%s = |%.10s|\n",s);
res = printf("testp %%s = |%.10s|\n",s);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
printf("\n\n");

//test NULL + precision < a len
resft = ft_printf("test %%s = |%.2s|\n",s);
res = printf("test %%s = |%.2s|\n",s);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
printf("\n\n");

//test NULL + precision 0
resft = ft_printf("test %%s = |%.s|\n",s);
res = printf("test %%s = |%.s|\n",s);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
printf("\n\n");

//test d
//flag autorise tous sauf #
//test des flags precision
int				d = 42;
resft = ft_printf("test %%d = |%-0# +30.5d|\n",d);
res = printf("test %%d = |%-0# +30.5d|\n",d);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
printf("\n\n");

//test avec val negative
d = -42;
resft = ft_printf("test %%d = |%-0# +30.5d|\n",d);
res = printf("test %%d = |%-0# +30.5d|\n",d);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
printf("\n\n");

//test sur val 0 et precision 0
d = 0;
resft = ft_printf("test %%d = |%.d|\n",d);
res = printf("test %%d = |%.d|\n",d);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
printf("\n\n");


//test %p
//flas autorise - et widht
char			*p = "hello";
resft = ft_printf("test %%p = |%-30.2p|\n",p);
res = printf("test %%p = |%-30.2p|\n",p);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
printf("\n\n");

//test p sur pointer NULL
p = NULL;
resft = ft_printf("test %%p = |%-30p|\n",p);
res = printf("test %%p = |%-30p|\n",p);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
printf("\n\n");

//avec precision
resft = ft_printf("test %%p = |%.2p|\n",p);
res = printf("test %%p = |%.2p|\n",p);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
printf("\n\n");


//test %u
//flags autorise -0.
unsigned int	u;
u = 4294967295;
resft = ft_printf("test %%u = |%-40.30u|\n",u);
res = printf("test %%u = |%-40.30u|\n",u);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
printf("\n\n");

//test x
unsigned int	x;
x = 429496729;
resft = ft_printf("test %%x = |%-40.30x|\n",x);
res = printf("test %%x = |%-40.30x|\n",x);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
printf("\n\n");

//test avec val 0
x = 0;
resft = ft_printf("test %%x = |%#-40.30x|\n",x);
res = printf("test %%x = |%#-40.30x|\n",x);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
printf("\n\n");

//test X
unsigned int	X;
X = 4294967;
resft = ft_printf("test %%X = |%-#40.30x|\n",X);
res = printf("test %%X = |%-#40.30x|\n",X);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
printf("\n\n");

//test avec val 0
X = 0;
resft = ft_printf("test %%x = |%#40.30x|\n",X);
res = printf("test %%x = |%#40.30x|\n",X);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
printf("\n\n");

//test d'un format invalide
X = 429496729;
resft = ft_printf("test %%X = |%&--5---+.###5 |\n",X);
res = printf("test %%X = |%&---5--+.###5 |\n",X);
printf("resft = %d\n",resft);
printf("res = %d\n",res);
printf("\n\n");
}
*/
