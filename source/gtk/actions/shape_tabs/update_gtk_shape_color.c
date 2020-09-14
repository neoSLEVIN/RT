/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_gtk_shape_color.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:21:05 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:21:06 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	update_gtk_shape_color(t_color_tab *tab, FLT3 color)
{
	GTK_CHANGER_SET_VALUE(tab->red.change, color.x);
	GTK_CHANGER_SET_VALUE(tab->green.change, color.y);
	GTK_CHANGER_SET_VALUE(tab->blue.change, color.z);
}
