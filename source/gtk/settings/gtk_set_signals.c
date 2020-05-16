/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/16 08:16:18 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_signals(t_rt *rt)
{
	g_signal_connect(G_OBJECT(rt->gtk->window), "key-press_event",
					G_CALLBACK(escape_window), NULL);
	g_signal_connect(G_OBJECT(rt->gtk->window), "key-press_event",
					G_CALLBACK(press_key_on_window), rt);
	g_signal_connect(G_OBJECT(rt->gtk->window), "key-release_event",
					G_CALLBACK(release_key_on_window), rt);
	g_signal_connect(G_OBJECT(rt->gtk->image_event_box), "button-press-event",
					G_CALLBACK(press_button_on_image_event_box), rt);
	g_signal_connect(G_OBJECT(rt->gtk->image_event_box), "button-release-event",
					G_CALLBACK(release_button_on_image_event_box), rt);
	g_signal_connect(G_OBJECT(rt->gtk->image_event_box), "motion_notify_event",
					G_CALLBACK(motion_button_on_image_event_box), rt);
	g_signal_connect (G_OBJECT(rt->gtk->fps_scale), "value-changed",
					G_CALLBACK (fps_scale_moved), rt);
	g_signal_connect(GTK_TOGGLE_BUTTON(rt->gtk->y_axis), "toggled",
					G_CALLBACK(change_axis), &rt->info->axis.y);
	g_signal_connect(GTK_TOGGLE_BUTTON(rt->gtk->x_axis), "toggled",
					G_CALLBACK(change_axis), &rt->info->axis.x);
	rt->gtk->timeout_id =
		g_timeout_add(1000 / rt->scene->fps, draw_by_timeout, rt);
}
