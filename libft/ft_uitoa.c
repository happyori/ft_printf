/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahirov <otahirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 18:42:37 by otahirov          #+#    #+#             */
/*   Updated: 2018/11/24 14:11:58 by otahirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_logic(char *str, int i, long long *l, bool *isnegative)
{
	if (*l == 0)
	{
		str[i++] = '0';
		str[i] = '\0';
		return (i);
	}
	if (*l < 0)
	{
		*isnegative = true;
		*l = -*l;
	}
	return (i);
}

char			*ft_uitoa(uintmax_t nb, int base, bool is_cap)
{
	bool		isnegative;
	int			i[2];
	long long	l;
	char		*str;
	char		c;

	l = nb;
	c = (is_cap) ? (c = 'A') : (c = 'a');
	CHECK_NULL((str = ft_strnew(ft_intlen(l))));
	isnegative = false;
	i[0] = ft_logic(str, 0, &l, &isnegative);
	while (l != 0)
	{
		i[1] = l % base;
		str[i[0]++] = (i[1] > 9) ? ((i[1] - 10) + c) : (i[1] + '0');
		l = l / base;
	}
	if (isnegative == TRUE)
		str[i[0]++] = '-';
	str[i[0]] = '\0';
	ft_reverse(str);
	return (str);
}