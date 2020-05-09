/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_print_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	pft_set_inf_nan(t_double *num, char type)
{
	if (num->is_inf)
		type == 'f' ?
			ft_strcpy(num->big, "fni") : ft_strcpy(num->big, "FNI");
	else
		type == 'f' ?
			ft_strcpy(num->big, "nan") : ft_strcpy(num->big, "NAN");
}

static void	pft_print_little_big(t_print *print, _Bool is_big)
{
	char	*str;
	int		len;
	size_t	i;

	str = is_big ? print->num.big : print->num.little;
	len = 0;
	i = ft_strlen(str);
	while ((i > 0) && str[i - 1] != 'R')
	{
		pft_print_wchar(print, str[--i]);
		++len;
	}
	if (!is_big && len < print->prop.precision)
		while (++len <= print->prop.precision)
			pft_print_wchar(print, '0');
}

static void	pft_print_f_3(t_print *print, int len)
{
	if (print->prop.precision > 0 || (print->prop.flag & FT_SHARP))
		pft_print_wchar(print, '.');
	if (!print->num.is_inf && !print->num.is_nan && print->prop.precision > 0)
		pft_print_little_big(print, 0);
	if (print->prop.flag & FT_MINUS)
		pft_print_indent(print, ' ', print->prop.width - len);
}

static void	pft_print_f_2(t_print *print)
{
	int		len;
	char	sign;

	if (print->num.sign)
		sign = '-';
	else if (print->prop.flag & (FT_PLUS + FT_SPACE))
		sign = (print->prop.flag & FT_PLUS) ? '+' : ' ';
	len = ft_strlen(print->num.big) + print->prop.precision;
	if (print->prop.precision > 0)
		++len;
	else if (print->prop.flag & FT_SHARP)
		++len;
	if (((print->prop.flag & (FT_SPACE + FT_PLUS)) || print->num.sign) &&
		!print->num.is_nan)
		++len;
	if (!(print->prop.flag & FT_MINUS) && !(print->prop.flag & FT_ZERO))
		pft_print_indent(print, ' ', print->prop.width - len);
	if (!print->num.is_nan &&
		((print->prop.flag & (FT_PLUS + FT_SPACE)) || print->num.sign))
		pft_print_wchar(print, sign);
	if (print->prop.flag & FT_ZERO)
		pft_print_indent(print, '0', print->prop.width - len);
	pft_print_little_big(print, 1);
	pft_print_f_3(print, len);
}

int			pft_print_f(t_print *print)
{
	if (print->prop.length == FT_LEN_BL)
		print->num.ld = (long double)(va_arg(print->args, long double));
	else
		print->num.d = (double)(va_arg(print->args, double));
	pft_calculate_f(&print->num, (print->prop.length == FT_LEN_BL));
	if (print->num.is_nan || print->num.is_inf)
	{
		pft_set_inf_nan(&print->num, print->prop.type);
		print->prop.precision = 0;
		print->prop.flag -= (print->prop.flag & (FT_ZERO + FT_SHARP));
	}
	else
	{
		if (print->prop.precision == -1)
			print->prop.precision = 6;
		pft_round_f(&print->num, print->prop.precision);
	}
	if (print->prop.flag & FT_MINUS)
		print->prop.flag -= (print->prop.flag & FT_ZERO);
	if (print->prop.flag & FT_PLUS)
		print->prop.flag -= (print->prop.flag & FT_SPACE);
	pft_print_f_2(print);
	return (print->len);
}
