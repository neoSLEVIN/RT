/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_print_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	pft_wchar_len(wchar_t c)
{
	if (c <= 0x7F)
		return (1);
	else if (c >= 0x80 && c <= 0x7FF)
		return (2);
	else if (c >= 0x800 && c <= 0xFFFF)
		return (3);
	else if (c >= 0x10000 && c <= 0x1FFFFF)
		return (4);
	else if (c >= 0x200000 && c <= 0x3FFFFFF)
		return (5);
	else if (c >= 0x4000000 && c <= 0x7FFFFFFF)
		return (6);
	return (0);
}

int			pft_print_c(t_print *print)
{
	wint_t	c;
	int		len;

	c = (char)va_arg(print->args, int);
	c = (wint_t)c;
	len = pft_wchar_len(c);
	if (!(print->prop.flag & FT_MINUS) && (print->prop.flag & FT_ZERO))
		pft_print_indent(print, '0', print->prop.width - len);
	else if (!(print->prop.flag & FT_MINUS))
		pft_print_indent(print, ' ', print->prop.width - len);
	pft_print_wchar(print, c);
	if (print->prop.flag & FT_MINUS)
		pft_print_indent(print, ' ', print->prop.width - len);
	return (print->len);
}
