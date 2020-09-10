/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spin_button_camera_position_changer.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:26:36 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:26:37 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static gboolean	spin_button_camera_position_changer_safe(gpointer data)
{
	t_rt			*rt;
	t_gtk_camera	*gtk_camera;

	rt = (t_rt*)data;
	gtk_camera = &rt->gtk->ui.camera;
	rt->scene->cam.dto->origin.x =
		gtk_spin_button_get_value(GTK_SPIN_BUTTON(gtk_camera->pos[0].spin));
	rt->scene->cam.dto->origin.y =
		gtk_spin_button_get_value(GTK_SPIN_BUTTON(gtk_camera->pos[1].spin));
	rt->scene->cam.dto->origin.z =
		gtk_spin_button_get_value(GTK_SPIN_BUTTON(gtk_camera->pos[2].spin));
	rt->info->update_cam = TRUE;
	rt->info->update = TRUE;
	return (FALSE);
}

void			spin_button_camera_position_changer(GtkSpinButton *button,
													gpointer data)
{
	(void)button;
	g_idle_add(spin_button_camera_position_changer_safe, data);
}
