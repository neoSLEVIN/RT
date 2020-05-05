/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_parse_flag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 06:12:37 by cschoen           #+#    #+#             */
/*   Updated: 2019/11/30 20:23:26 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void	pft_parse_flag(t_print *print)
{
	while (pft_is_flag(&print->cur[print->i]))
	{
		if (print->cur[print->i] == '#')
			print->prop.flag |= FT_SHARP;
		else if (print->cur[print->i] == '+')
			print->prop.flag |= FT_PLUS;
		else if (print->cur[print->i] == '-')
			print->prop.flag |= FT_MINUS;
		else if (print->cur[print->i] == ' ')
			print->prop.flag |= FT_SPACE;
		else if (print->cur[print->i] == '0')
			print->prop.flag |= FT_ZERO;
		++print->i;
	}
}
