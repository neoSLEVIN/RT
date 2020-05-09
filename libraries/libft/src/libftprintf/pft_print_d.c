/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_print_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static intmax_t	pft_get_num_type(t_print *print)
{
	intmax_t	num;

	if (print->prop.length == FT_LEN_HH)
		num = (signed char)(va_arg(print->args, int));
	else if (print->prop.length == FT_LEN_H)
		num = (short)(va_arg(print->args, int));
	else if (print->prop.length == FT_LEN_L)
		num = (long)(va_arg(print->args, long int));
	else if (print->prop.length == FT_LEN_LL)
		num = (long long)(va_arg(print->args, long long int));
	else if (print->prop.length == FT_LEN_J)
		num = (intmax_t)(va_arg(print->args, intmax_t));
	else if (print->prop.length == FT_LEN_Z)
		num = (size_t)(va_arg(print->args, size_t));
	else
		num = (int)(va_arg(print->args, int));
	return ((intmax_t)num);
}

static int		pft_get_width(intmax_t num)
{
	int	width;

	if (num == -9223372036854775807 - 1)
		return (19);
	if (num < 0)
		num *= -1;
	width = 1;
	while ((num /= 10) > 0)
		++width;
	return (width);
}

void			pft_print_abs_integer(intmax_t num, int *len, int fd)
{
	if (num == -9223372036854775807 - 1)
	{
		write(fd, "9223372036854775808", 19);
		*len += 19;
	}
	else
	{
		if (num < 0)
			num *= -1;
		if (num > 9)
			pft_print_abs_integer(num / 10, len, fd);
		ft_putchar_fd((num % 10) + '0', fd);
		*len += 1;
	}
}

static void		pft_print_d_2(t_print *print, intmax_t num, int width,
								_Bool left)
{
	char	sign_char;
	int		precision;

	sign_char = '\0';
	if (num < 0)
		sign_char = '-';
	else if (print->prop.flag & FT_PLUS)
		sign_char = '+';
	else if (print->prop.flag & FT_SPACE)
		sign_char = ' ';
	num *= ((num < 0) && num != (-9223372036854775807 - 1)) ? -1 : 1;
	precision = (print->prop.precision > width) ? print->prop.precision : width;
	if (sign_char)
		++precision;
	if (!left)
		pft_print_indent(print, ' ', print->prop.width - precision);
	if (sign_char)
		pft_print_wchar(print, sign_char);
	pft_print_indent(print, '0', print->prop.precision - width);
	pft_print_abs_integer(num, &print->len, print->fd);
	if (left)
		pft_print_indent(print, ' ', print->prop.width - precision);
}

int				pft_print_d(t_print *print)
{
	int			flag;
	_Bool		is_space_plus;
	intmax_t	num;

	flag = print->prop.flag;
	is_space_plus = ((flag & (FT_PLUS + FT_SPACE)) != 0);
	num = pft_get_num_type(print);
	if (num == 0 && print->prop.precision == 0)
	{
		if (!(flag & FT_MINUS))
			pft_print_indent(print, ' ', print->prop.width - is_space_plus);
		if (is_space_plus)
			pft_print_wchar(print, ((flag & FT_PLUS) ? '+' : ' '));
		if (flag & FT_MINUS)
			pft_print_indent(print, ' ', print->prop.width - is_space_plus);
		return (print->len);
	}
	if ((flag & FT_ZERO) && (print->prop.precision == -1) && !(flag & FT_MINUS))
	{
		print->prop.precision = print->prop.width;
		if (num < 0 || is_space_plus)
			--print->prop.precision;
	}
	pft_print_d_2(print, num, pft_get_width(num), ((flag & FT_MINUS) != 0));
	return (print->len);
}
