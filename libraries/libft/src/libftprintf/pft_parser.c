/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	pft_reset_print(t_print *print, int len)
{
	ft_strdel(&print->num.big);
	ft_strdel(&print->num.little);
	ft_strdel(&print->num.summand);
	ft_strdel(&print->num.temp);
	va_end(print->args);
	return (len);
}

static void	pft_reset_num(t_double *num)
{
	num->ld = 0;
	num->d = 0;
	num->sign = 0;
	num->exp = 0;
	num->mantissa = 0;
	num->is_inf = 0;
	num->is_nan = 0;
	ft_bzero(num->big, FT_NUM_LENGTH);
	ft_bzero(num->little, FT_NUM_LENGTH);
	ft_bzero(num->summand, FT_NUM_LENGTH);
	ft_bzero(num->temp, FT_NUM_LENGTH);
	*num->big = '0';
	*num->little = '0';
	*num->summand = '0';
	*num->temp = '0';
}

static void	pft_reset_prop(t_prop *prop)
{
	prop->color_flg = 0;
	prop->fd_flg = 0;
	prop->flag = 0;
	prop->width = 0;
	prop->precision = -1;
	prop->length = 0;
	prop->type = '\0';
}

static int	pft_parse_prop(t_print *print)
{
	++print->i;
	pft_parse_addition(print);
	while (pft_is_prop(&print->cur[print->i]))
	{
		if (pft_is_flag(&print->cur[print->i]))
			pft_parse_flag(print);
		if (print->cur[print->i] >= '1' && print->cur[print->i] <= '9')
			pft_parse_width(print);
		if (print->cur[print->i] == '.')
			pft_parse_precision(print);
		if (pft_is_length(&print->cur[print->i]))
			pft_parse_length(print);
	}
	pft_parse_type(print);
	if (print->prop.fd_flg & 1)
		print->fd = (int)va_arg(print->args, int);
	if (print->prop.color_flg & 1)
		pft_choose_color(print);
	return (pft_choose_type(print));
}

int			pft_parser(t_print *print)
{
	if (ft_strequ(print->cur, "%"))
		return (pft_reset_print(print, 0));
	while (print->cur[print->i] != '\0')
	{
		if (print->cur[print->i] == '%')
		{
			pft_reset_prop(&print->prop);
			if (pft_parse_prop(print) == -1)
				return (pft_reset_print(print, -1));
			if (print->prop.fd_flg & 2)
				print->fd = 0;
			if (print->prop.color_flg & 2)
				pft_print_color(print, "\033[0m");
			if (print->prop.type == 'f' || print->prop.type == 'F')
				pft_reset_num(&print->num);
		}
		else
			pft_print_wchar(print, print->cur[print->i++]);
	}
	return (pft_reset_print(print, print->len));
}
