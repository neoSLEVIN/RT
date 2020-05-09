/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_print_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static uintmax_t	pft_get_num_type(t_print *print)
{
	uintmax_t	num;

	if (print->prop.length == FT_LEN_HH)
		num = (unsigned char)(va_arg(print->args, unsigned int));
	else if (print->prop.length == FT_LEN_H)
		num = (unsigned short)(va_arg(print->args, unsigned int));
	else if (print->prop.length == FT_LEN_L)
		num = (unsigned long)(va_arg(print->args, unsigned long int));
	else if (print->prop.length == FT_LEN_LL)
		num = (unsigned long long)(va_arg(print->args, unsigned long long int));
	else if (print->prop.length == FT_LEN_J)
		num = (uintmax_t)(va_arg(print->args, uintmax_t));
	else if (print->prop.length == FT_LEN_Z)
		num = (size_t)(va_arg(print->args, size_t));
	else
		num = (unsigned int)(va_arg(print->args, unsigned int));
	return ((uintmax_t)num);
}

static int			pft_get_width(uintmax_t num)
{
	int	width;

	width = 1;
	while ((num /= 10) > 0)
		++width;
	return (width);
}

static void			pft_print_uinteger(uintmax_t num, int *len, int fd)
{
	if (num > 9)
		pft_print_uinteger(num / 10, len, fd);
	ft_putchar_fd((num % 10) + '0', fd);
	*len += 1;
}

int					pft_print_u(t_print *print)
{
	uintmax_t	num;
	int			flag;
	int			width;
	int			precision;

	flag = print->prop.flag;
	num = pft_get_num_type(print);
	if (num == 0 && print->prop.precision == 0)
	{
		pft_print_indent(print, ' ', print->prop.width);
		return (print->len);
	}
	if ((flag & FT_ZERO) && (print->prop.precision == -1) && !(flag & FT_MINUS))
		print->prop.precision = print->prop.width;
	width = pft_get_width(num);
	precision = (print->prop.precision > width) ? print->prop.precision : width;
	if (!(flag & FT_MINUS))
		pft_print_indent(print, ' ', print->prop.width - precision);
	pft_print_indent(print, '0', print->prop.precision - width);
	pft_print_uinteger(num, &print->len, print->fd);
	if (flag & FT_MINUS)
		pft_print_indent(print, ' ', print->prop.width - precision);
	return (print->len);
}
