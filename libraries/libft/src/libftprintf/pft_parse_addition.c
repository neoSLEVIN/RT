/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_parse_addition.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

static int	pft_is_addition(char *c)
{
	return (*c == '{' || *c == '}' || *c == '[' || *c == ']');
}

void		pft_parse_addition(t_print *print)
{
	while (pft_is_addition(&print->cur[print->i]))
	{
		if (print->cur[print->i] == '{')
			print->prop.color_flg |= 1;
		else if (print->cur[print->i] == '}')
			print->prop.color_flg |= 2;
		else if (print->cur[print->i] == '[')
			print->prop.fd_flg |= 1;
		else if (print->cur[print->i] == ']')
			print->prop.fd_flg |= 2;
		++print->i;
	}
}
