/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 06:13:51 by cschoen           #+#    #+#             */
/*   Updated: 2019/11/30 20:24:16 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void	pft_parse_type(t_print *print)
{
	if (pft_is_type(&print->cur[print->i]))
	{
		print->prop.type = print->cur[print->i];
		++print->i;
	}
}
