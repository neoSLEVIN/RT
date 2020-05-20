/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_positions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/20 21:15:19 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static void	gtk_set_settings_positions(t_gtk_settings *settings)
{
	gtk_container_add(GTK_CONTAINER(settings->expander),
						GTK_WIDGET(settings->grid));
	gtk_grid_attach(GTK_GRID(settings->grid), settings->fps_label, 0, 0, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(settings->grid), settings->fps_scale,
			settings->fps_label, GTK_POS_RIGHT, 8, 1);
	gtk_grid_attach_next_to(GTK_GRID(settings->grid), settings->y_axis,
			settings->fps_label, GTK_POS_BOTTOM, 3, 1);
	gtk_grid_attach_next_to(GTK_GRID(settings->grid), settings->separator,
			settings->y_axis, GTK_POS_RIGHT, 3, 1);
	gtk_grid_attach_next_to(GTK_GRID(settings->grid), settings->x_axis,
			settings->separator, GTK_POS_RIGHT, 3, 1);

}

void		gtk_set_positions(t_gtk *gtk)
{
	gtk_container_add(GTK_CONTAINER(gtk->window), gtk->window_h_box);
	gtk_box_pack_start(GTK_BOX(gtk->window_h_box),
		GTK_WIDGET(gtk->img.image_event_box), FALSE, FALSE, 0);
	gtk_container_add(GTK_CONTAINER(gtk->img.image_event_box),
		GTK_WIDGET(gtk->img.image));
	gtk_box_pack_start(GTK_BOX(gtk->window_h_box), gtk->ui.grid, TRUE, TRUE, 5);
	gtk_set_settings_positions(&gtk->ui.settings);
	gtk_grid_attach(GTK_GRID(gtk->ui.grid),
		gtk->ui.settings.expander, 0, 0, 1, 1);
	gtk_grid_attach_next_to(GTK_GRID(gtk->ui.grid), gtk->button, gtk->ui.settings.expander, GTK_POS_BOTTOM, 1, 1);
}
