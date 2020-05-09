/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_print_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	pft_print_p_2(t_print *print, char *str, _Bool left)
{
	int	precision;
	int	width;

	width = ft_strlen(str);
	precision = (print->prop.precision > width) ? print->prop.precision : width;
	precision += 2;
	if (!left)
		pft_print_indent(print, ' ', print->prop.width - precision);
	write(print->fd, "0x", 2);
	print->len += 2;
	pft_print_indent(print, '0', print->prop.precision - width);
	if (print->prop.precision != 0)
	{
		ft_putstr_fd(str, print->fd);
		print->len += width;
	}
	if (left)
		pft_print_indent(print, ' ', print->prop.width - precision);
}

int			pft_print_p(t_print *print)
{
	uintmax_t	num;
	char		*str;
	int			flag;

	flag = print->prop.flag;
	num = (uintmax_t)(va_arg(print->args, unsigned long int));
	if (!(str = ft_itoa_base(num, 16, 'a')))
		return (-1);
	if ((flag & FT_ZERO) && (print->prop.precision == -1) && !(flag & FT_MINUS))
		print->prop.precision = print->prop.width - 2;
	pft_print_p_2(print, str, ((flag & FT_MINUS) != 0));
	ft_strdel(&str);
	return (print->len);
}
