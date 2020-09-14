/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_color_tab_widgets.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:28:58 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:28:58 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_color_tab_widgets(t_color_tab *color_tab, FLT3 *color)
{
	color_tab->label = gtk_label_new("Texture/Color");
	color_tab->scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(
		color_tab->scrolled_window), 370);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(
		color_tab->scrolled_window),
		GTK_POLICY_AUTOMATIC, GTK_POLICY_NEVER);
	color_tab->v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	color_tab->grid = gtk_grid_new();
	color_tab->red =
		gtk_set_spinner_float("Red:", (FLT2){0.0f, 1.0f}, color->x, 0.001f);
	color_tab->green =
		gtk_set_spinner_float("Green:", (FLT2){0.0f, 1.0f}, color->y, 0.001f);
	color_tab->blue =
		gtk_set_spinner_float("Blue:", (FLT2){0.0f, 1.0f}, color->z, 0.001f);
}
