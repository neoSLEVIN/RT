/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov_scale_moved.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:25:31 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:25:31 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static gboolean	fov_scale_moved_safe(gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	rt->scene->cam.fov =
		gtk_spin_button_get_value(GTK_SPIN_BUTTON(rt->gtk->ui.camera.fov.spin));
	init_dto_cam(rt->scene->cam.dto, rt->scene->cam.fov,
				rt->scene->cam.display);
	rt->info->update_cam = TRUE;
	rt->info->update = TRUE;
	return (FALSE);
}

void			fov_scale_moved(GtkSpinButton *button, gpointer data)
{
	(void)button;
	g_idle_add(fov_scale_moved_safe, data);
}
