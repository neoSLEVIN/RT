/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_parse_length.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void	pft_parse_length(t_print *print)
{
	if (pft_is_length(&print->cur[print->i]) && !print->prop.length)
	{
		if (print->cur[print->i] == 'j')
			print->prop.length = FT_LEN_J;
		else if (print->cur[print->i] == 'z')
			print->prop.length = FT_LEN_Z;
		else if (print->cur[print->i] == 'L')
			print->prop.length = FT_LEN_BL;
		else if (print->cur[print->i] == 'l' && print->cur[print->i + 1] == 'l')
			print->prop.length = FT_LEN_LL;
		else if (print->cur[print->i] == 'l')
			print->prop.length = FT_LEN_L;
		else if (print->cur[print->i] == 'h' && print->cur[print->i + 1] == 'h')
			print->prop.length = FT_LEN_HH;
		else if (print->cur[print->i] == 'h')
			print->prop.length = FT_LEN_H;
		++print->i;
		if (print->prop.length == FT_LEN_LL || print->prop.length == FT_LEN_HH)
			++print->i;
	}
	while (pft_is_length(&print->cur[print->i]))
		++print->i;
}
