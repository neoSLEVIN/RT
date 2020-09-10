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

void	update_gtk_shape_color(t_color_tab tab, FLT3 color)
{
	if (!gtk_widget_get_visible(tab.color))
		gtk_widget_set_visible(tab.color, TRUE);
	gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(tab.color),
							&(GdkRGBA){color.x, color.y, color.z, 1});
}
