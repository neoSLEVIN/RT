/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_print_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	pft_print_s(t_print *print)
{
	char	*str;
	int		len;

	str = (char *)va_arg(print->args, char *);
	len = str ? ft_strlen(str) : 6;
	if (!(print->prop.flag & FT_MINUS))
	{
		if (print->prop.precision == -1 && print->prop.flag & FT_ZERO)
			pft_print_indent(print, '0', print->prop.width - len);
		else if (print->prop.precision == -1 || print->prop.precision >= len)
			pft_print_indent(print, ' ', print->prop.width - len);
		else
			pft_print_indent(print, ' ',
				print->prop.width - print->prop.precision);
	}
	if (print->prop.precision > -1 && print->prop.precision < len)
		len = print->prop.precision;
	write(print->fd, str ? str : "(null)", len);
	print->len += len;
	if (print->prop.flag & FT_MINUS)
		pft_print_indent(print, ' ', print->prop.width - len);
	return (print->len);
}
