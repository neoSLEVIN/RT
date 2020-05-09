/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_parse_precision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void	pft_parse_precision(t_print *print)
{
	int	dot;

	dot = -1;
	print->prop.precision = -1;
	while (print->cur[print->i] == '.')
	{
		print->prop.precision = 0;
		dot = 0;
		++print->i;
	}
	while (print->cur[print->i] >= '0' && print->cur[print->i] <= '9')
	{
		print->prop.precision *= 10;
		print->prop.precision += (print->cur[print->i] - 48);
		++print->i;
	}
	if (print->prop.precision < 0)
		print->prop.precision = dot;
}
