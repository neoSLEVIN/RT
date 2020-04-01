/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 20:27:14 by cschoen           #+#    #+#             */
/*   Updated: 2019/11/30 20:42:17 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

int	pft_print_other(t_print *print)
{
	if (!print->cur[print->i] && !print->len)
		return (0);
	return (print->len);
}
