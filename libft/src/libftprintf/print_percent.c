/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_percent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 20:16:41 by cschoen           #+#    #+#             */
/*   Updated: 2019/11/30 20:42:08 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	pft_print_percent(t_print *print)
{
	if (print->prop.flag & FT_MINUS)
		print->prop.flag -= (print->prop.flag & FT_ZERO);
	if (!(print->prop.flag & (FT_MINUS + FT_ZERO)))
		pft_print_indent(print, ' ', print->prop.width - 1);
	else if (print->prop.flag & FT_ZERO)
		pft_print_indent(print, '0', print->prop.width - 1);
	write(print->fd, "%", 1);
	++print->len;
	if (print->prop.flag & FT_MINUS)
		pft_print_indent(print, ' ', print->prop.width - 1);
	return (print->len);
}
