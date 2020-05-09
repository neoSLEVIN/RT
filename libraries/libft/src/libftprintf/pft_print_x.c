/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_print_x.c                                      :+:      :+:    :+:   */
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

static void			pft_print_x_2(t_print *print, uintmax_t num, char *str,
								_Bool left)
{
	int	precision;
	int	width;
	int	flag;

	flag = print->prop.flag;
	width = ft_strlen(str);
	if ((flag & FT_ZERO) && (print->prop.precision == -1) && !(flag & FT_MINUS))
	{
		print->prop.precision = print->prop.width;
		((print->prop.flag & FT_SHARP) && num) ? width += 2 : 0;
	}
	precision = (print->prop.precision > width) ? print->prop.precision : width;
	if ((print->prop.flag & FT_SHARP) && num)
		precision += 2;
	(!left) ? pft_print_indent(print, ' ', print->prop.width - precision) : 0;
	if ((print->prop.flag & FT_SHARP) && num)
	{
		write(print->fd, (print->prop.type == 'x' ? "0x" : "0X"), 2);
		print->len += 2;
	}
	pft_print_indent(print, '0', print->prop.precision - width);
	ft_putstr_fd(str, print->fd);
	print->len += ft_strlen(str);
	(left) ? pft_print_indent(print, ' ', print->prop.width - precision) : 0;
}

int					pft_print_x(t_print *print)
{
	uintmax_t	num;
	char		*str;

	num = pft_get_num_type(print);
	if (num == 0 && print->prop.precision == 0)
	{
		pft_print_indent(print, ' ', print->prop.width);
		return (print->len);
	}
	if (!(str = ft_itoa_base(num, 16, ((print->prop.type == 'x') ? 'a' : 'A'))))
		return (-1);
	pft_print_x_2(print, num, str, ((print->prop.flag & FT_MINUS) != 0));
	ft_strdel(&str);
	return (print->len);
}
