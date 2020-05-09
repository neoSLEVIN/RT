/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_choose_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

int	pft_choose_type(t_print *print)
{
	char	type;

	type = print->prop.type;
	if (type == 'd' || type == 'i')
		return (pft_print_d(print));
	else if (type == 'u')
		return (pft_print_u(print));
	else if (type == 'o')
		return (pft_print_o(print));
	else if (type == 'x' || type == 'X')
		return (pft_print_x(print));
	else if (type == 'f' || type == 'F')
		return (pft_print_f(print));
	else if (type == 'c')
		return (pft_print_c(print));
	else if (type == 's')
		return (pft_print_s(print));
	else if (type == 'p')
		return (pft_print_p(print));
	else if (type == '%')
		return (pft_print_percent(print));
	return (pft_print_other(print));
}
