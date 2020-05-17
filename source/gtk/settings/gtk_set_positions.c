/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_positions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/10 07:08:10 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_positions(t_gtk *gtk)
{
	gtk_container_add(GTK_CONTAINER(gtk->window), gtk->h_box);
	gtk_box_pack_start(GTK_BOX(gtk->h_box), GTK_WIDGET(gtk->image_event_box),
					FALSE, FALSE, 0);
	gtk_container_add(GTK_CONTAINER(gtk->image_event_box),
					GTK_WIDGET(gtk->image));
	gtk_box_pack_start(GTK_BOX(gtk->h_box), gtk->ui_v_box, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(gtk->ui_v_box), gtk->fps_h_box, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(gtk->fps_h_box), gtk->fps_label,
					FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(gtk->fps_h_box), gtk->fps_scale, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(gtk->ui_v_box), gtk->y_axis, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(gtk->ui_v_box), gtk->x_axis, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(gtk->ui_v_box), gtk->button, FALSE, FALSE, 0);
}
