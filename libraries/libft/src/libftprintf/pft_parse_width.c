/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_parse_width.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 06:13:10 by cschoen           #+#    #+#             */
/*   Updated: 2019/11/30 20:24:30 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void	pft_parse_width(t_print *print)
{
	print->prop.width = 0;
	while (print->cur[print->i] >= '0' && print->cur[print->i] <= '9')
	{
		print->prop.width *= 10;
		print->prop.width += (print->cur[print->i] - 48);
		++print->i;
	}
	if (print->prop.width < 0)
		print->prop.width = 0;
}
