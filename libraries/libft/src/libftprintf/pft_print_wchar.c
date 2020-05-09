/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_print_wchar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	pft_print_oct(t_print *print, wchar_t c, size_t cnt)
{
	unsigned char	res[6];

	if (cnt == 2)
		res[0] = (c >> 6) + 0xc0;
	else if (cnt == 3)
		res[0] = (c >> 12) + 0xe0;
	else if (cnt == 4)
		res[0] = (c >> 18) + 0xf0;
	else if (cnt == 5)
		res[0] = (c >> 24) + 0xf8;
	else if (cnt == 6)
	{
		res[0] = (c >> 30) + 0xfc;
		res[1] = ((c >> 24) & 0x3f) + 0x80;
	}
	cnt > 4 ? res[cnt - 4] = ((c >> 18) & 0x3f) + 0x80 : 0;
	cnt > 3 ? res[cnt - 3] = ((c >> 12) & 0x3f) + 0x80 : 0;
	cnt > 2 ? res[cnt - 2] = ((c >> 6) & 0x3f) + 0x80 : 0;
	res[cnt - 1] = (c & 0x3f) + 0x80;
	write(print->fd, res, cnt);
	print->len += cnt;
}

void		pft_print_wchar(t_print *print, wchar_t c)
{
	if (c <= 0x7F)
	{
		write(print->fd, &c, 1);
		print->len += 1;
	}
	else if (c >= 0x80 && c <= 0x7FF)
		pft_print_oct(print, c, 2);
	else if (c >= 0x800 && c <= 0xFFFF)
		pft_print_oct(print, c, 3);
	else if (c >= 0x10000 && c <= 0x1FFFFF)
		pft_print_oct(print, c, 4);
	else if (c >= 0x200000 && c <= 0x3FFFFFF)
		pft_print_oct(print, c, 5);
	else if (c >= 0x4000000 && c <= 0x7FFFFFFF)
		pft_print_oct(print, c, 6);
}
