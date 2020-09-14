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
	t_changer	*changer;

	rt = (t_rt*)data;
	changer = &rt->gtk->ui.camera.display_width;
	rt->scene->cam.display.x = GTK_CHANGER_GET_VALUE(changer->change);
	init_dto_cam(rt->scene->cam.dto, rt->scene->cam.fov,
				rt->scene->cam.display);
	rt->info->update_cam = TRUE;
	rt->info->update = TRUE;
	return (FALSE);
}

void			display_width_scale_moved(GtkWidget *button, gpointer data)
{
	(void)button;
	g_idle_add(display_width_scale_moved_safe, data);
}

static gboolean	display_height_scale_moved_safe(gpointer data)
{
	t_rt		*rt;
	t_changer	*changer;

	rt = (t_rt*)data;
	changer = &rt->gtk->ui.camera.display_height;
	rt->scene->cam.display.y = GTK_CHANGER_GET_VALUE(changer->change);
	init_dto_cam(rt->scene->cam.dto, rt->scene->cam.fov,
				rt->scene->cam.display);
	rt->info->update_cam = TRUE;
	rt->info->update = TRUE;
	return (FALSE);
}

void			display_height_scale_moved(GtkWidget *button, gpointer data)
{
	(void)button;
	g_idle_add(display_height_scale_moved_safe, data);
}
