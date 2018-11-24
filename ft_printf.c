/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahirov <otahirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 18:08:04 by otahirov          #+#    #+#             */
/*   Updated: 2018/11/20 17:09:35 by otahirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void ft_flags(const char **form)
{
	if (**form == '-')
		g_flags[0] = true;
	else if (**form == '+')
		g_flags[1] = true;
	else if (**form == '0')
		g_flags[2] = true;
	else if (**form == ' ' && g_flags[2] != true)
		g_flags[3] = true;
	else if (**form == '#')
		g_flags[4] = true;
}

static void	ft_lenmods(const char **form)
{
	if (**form == 'l' && **(form + 1) != 'l')
		g_lenmod[0] = true;
	else if (**form == 'l' && **(form + 1) == 'l')
	{
		g_lenmod[1] = true;
		*form += 1;
	}
	else if (**form == 'h' && **(form + 1) != 'h')
		g_lenmod[2] = true;
	else if (**form == 'h' && **(form + 1) == 'h')
	{
		g_lenmod[3] = true;
		*form += 1;
	}
	else if (**form == 'L')
		g_lenmod[4] = true;
	else if (**form == 'j')
		g_lenmod[5] = true;
}

static void	ft_conv(const char **form, va_list ap)
{
	char	*field;
	size_t	ln;

	ln = 0;
	field = ft_strnew(10);
	while (**form && !CONV(**form))
	{
		if (FLAGS(**form))
			ft_flags(form);
		else if (**form == '*')
			g_flags[5] = true;
		else if (ft_isdigit(**form) && g_flags[6] != true)
			field[ln++] = **form;
		else if (**form == '.')
			g_flags[6] = true;
		else if (ft_isdigit(**form) && g_flags[6] == true)
			g_precision = ft_scanint((char **)form);
		else if (LENMOD(**form))
			ft_lenmods(form);
		*form += 1;
	}
	ln = 0;
	if (CONV(**form))
		while (ln < TABLE_SIZE)
			if (g_table[ln++].flag == **form)
				g_table[ln - 1].func(ap, **form);
}

static void	reset_glob(void)
{
	int		i;

	i = 0;
	g_bytes = 0;
	g_precision = 0;
	while (i < G_LENMOD)
		g_lenmod[i++] = false;
	i = 0;
	while (i < G_FLAGS)
		g_flags[i++] = false;
}

/*
** Format:
** % [flags] [field_width] [.precision] [length_modifier] convertional_modifier
*/

int		ft_printf(const char *format, ...)
{
	va_list		print;

	va_start(print, format);
	reset_glob();
	while (*format)
	{
		if (*format == '%')
		{
			if (*(format + 1) == '%')
			{
				g_bytes += ft_putchar('%');
				format++;
			}
			else
				ft_conv(&format, print);
		}
		else if (*format == '{')
			format += color(format);
		else
			g_bytes += ft_putchar(*format);
		format++;
	}
	va_end(print);
	return (g_bytes);
}
