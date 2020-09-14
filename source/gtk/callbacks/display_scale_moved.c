/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_scale_moved.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:25:21 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:25:22 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static gboolean	display_width_scale_moved_safe(gpointer data)
{
	t_rt		*rt;
	t_spinner	*spinner;

	rt = (t_rt*)data;
	spinner = &rt->gtk->ui.camera.display_width;
	rt->scene->cam.display.x =
		gtk_spin_button_get_value(GTK_SPIN_BUTTON(spinner->spin));
	init_dto_cam(rt->scene->cam.dto, rt->scene->cam.fov,
				rt->scene->cam.display);
	rt->info->update_cam = TRUE;
	rt->info->update = TRUE;
	return (FALSE);
}

void			display_width_scale_moved(GtkSpinButton *button, gpointer data)
{
	(void)button;
	g_idle_add(display_width_scale_moved_safe, data);
}

static gboolean	display_height_scale_moved_safe(gpointer data)
{
	t_rt		*rt;
	t_spinner	*spinner;

	rt = (t_rt*)data;
	spinner = &rt->gtk->ui.camera.display_height;
	rt->scene->cam.display.y =
			gtk_spin_button_get_value(GTK_SPIN_BUTTON(spinner->spin));
	init_dto_cam(rt->scene->cam.dto, rt->scene->cam.fov,
				rt->scene->cam.display);
	rt->info->update_cam = TRUE;
	rt->info->update = TRUE;
	return (FALSE);
}

void			display_height_scale_moved(GtkSpinButton *button, gpointer data)
{
	(void)button;
	g_idle_add(display_height_scale_moved_safe, data);
}
