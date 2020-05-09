/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/09 15:30:54 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	pft_is_color_type(int color)
{
	return (color == FT_EOC || color == FT_RED || color == FT_GREEN ||
			color == FT_BLUE || color == FT_YELLOW || color == FT_PURPLE ||
			color == FT_CYAN);
}

void		pft_print_color(t_print *print, char *color)
{
	ft_putstr_fd(color, print->fd);
	print->len += ft_strlen(color);
}

void		pft_choose_color(t_print *print)
{
	int	color_type;

	color_type = (int)va_arg(print->args, int);
	if (!pft_is_color_type(color_type))
		pft_print_color(print, "\033[0m");
	else if (color_type == FT_EOC)
		pft_print_color(print, "\033[0m");
	else if (color_type == FT_RED)
		pft_print_color(print, "\033[31m");
	else if (color_type == FT_GREEN)
		pft_print_color(print, "\033[32m");
	else if (color_type == FT_BLUE)
		pft_print_color(print, "\033[34m");
	else if (color_type == FT_YELLOW)
		pft_print_color(print, "\033[33m");
	else if (color_type == FT_PURPLE)
		pft_print_color(print, "\033[35m");
	else if (color_type == FT_CYAN)
		pft_print_color(print, "\033[36m");
}
