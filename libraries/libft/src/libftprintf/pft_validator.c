/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

int		pft_is_prop(char *c)
{
	return (pft_is_flag(c) || pft_is_length(c) || *c == '.' ||
			(*c >= '0' && *c <= '9'));
}

int		pft_is_flag(char *c)
{
	return (*c == '#' || *c == '+' || *c == '-' || *c == ' ' || *c == '0');
}

int		pft_is_length(char *c)
{
	return (*c == 'h' || *c == 'l' || *c == 'L' || *c == 'j' || *c == 'z');
}

int		pft_is_type(char *c)
{
	return (*c == 'c' || *c == 's' || *c == 'p' || *c == '%' || *c == 'd' ||
			*c == 'i' || *c == 'u' || *c == 'o' || *c == 'x' || *c == 'X' ||
			*c == 'f' || *c == 'F');
}

void	pft_is_inf_nan(t_double *num, _Bool is_long)
{
	unsigned long long	tail;

	tail = num->mantissa & (unsigned long long)0x3FFFFFFFFFFFFFFF;
	if (is_long)
	{
		if ((num->exp >> 8) == (unsigned short)0x7F)
		{
			if (((num->mantissa >> 62) & (unsigned long long)1) && !tail)
				num->is_inf = (num->sign) ? -1 : 1;
			else
				num->is_nan = 1;
		}
	}
	else
	{
		if (num->exp == (unsigned short)0x7FF0)
		{
			if (num->mantissa == (unsigned long long)0x10000000000000)
				num->is_inf = (num->sign) ? -1 : 1;
			else
				num->is_nan = 1;
		}
	}
}
