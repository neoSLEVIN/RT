/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_scale_moved.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 05:02:06 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/10 06:57:52 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

static gboolean	fps_scale_moved_safe(gpointer data)
{
	t_rt	*rt;

	rt = (t_rt*)data;
	rt->scene->cam.fps =
		gtk_spin_button_get_value(GTK_SPIN_BUTTON(rt->gtk->ui.camera.fps.spin));
	g_source_remove(rt->gtk->timeout_id);
	rt->gtk->timeout_id =
			g_timeout_add(1000 / rt->scene->cam.fps, draw_by_timeout, rt);
	return (FALSE);
}

void			fps_scale_moved(GtkSpinButton *button, gpointer data)
{
	(void)button;
	g_idle_add(fps_scale_moved_safe, data);
}
