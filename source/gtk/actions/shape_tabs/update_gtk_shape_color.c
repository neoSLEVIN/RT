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
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab->red.spin), color.x);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab->green.spin), color.y);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(tab->blue.spin), color.z);
}
