/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_floats.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahirov <otahirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 18:47:33 by otahirov          #+#    #+#             */
/*   Updated: 2018/11/23 17:35:50 by otahirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern bool g_flags[];
extern bool g_lenmod[];

static long double	pullFloat(va_list ap)
{
	long double		input;

	if (g_lenmod[0])
		input = (long double)va_arg(ap, double);
	else if (g_lenmod[4])
		input = va_arg(ap, long double);
	else
		input = (long double)va_arg(ap, double);
	return (input);
}

static long			afterpointCalc(long double nb)
{
	long		ln;
	int			inb;

	inb = (int)nb;
	ln = 0;
	while ((nb - (long double)inb) > 0)
	{
		nb *= 10;
		ln++;
		inb = (int)nb;
		if (ln >= 100)
			return (-1);
	}
	return (ln);
}

void				print_f(va_list ap, char fg)
{
	int			iIn;
	long double	fIn;
	char		*str;
	long		ln;

	if (fg != 'f' && fg != 'F' && fg != 'e' && fg != 'E')
		return ;
	fIn = pullFloat(ap);
	iIn = (int)fIn;
	fIn -= (float)iIn;
	str = ft_itoa((intmax_t)iIn, 10, false);
	//?if((ln = afterpointCalc(fIn.ld)) == -1)
	if ((ln = afterpointCalc(fIn)) == -1)
		
	if (g_flags[4])
	{
		//TODO: ADD TO STR THE '.'
		//TODO: ADD ALL OF THE after. NUMBERS
	}
}
