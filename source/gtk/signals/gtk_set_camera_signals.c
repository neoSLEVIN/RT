/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_camera_signals.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:27:52 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:27:52 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_camera_signals(t_rt *rt)
{
	t_gtk_camera	*camera;

	camera = &rt->gtk->ui.camera;
	g_signal_connect(G_OBJECT(camera->expander), "notify::expanded",
		G_CALLBACK(camera_expander_callback), rt);
	g_signal_connect(G_OBJECT(camera->pos_expander), "notify::expanded",
		G_CALLBACK(camera_expander_callback), rt);
	g_signal_connect(GTK_TOGGLE_BUTTON(camera->y_axis), "toggled",
		G_CALLBACK(change_axis), &rt->info->axis.y);
	g_signal_connect(GTK_TOGGLE_BUTTON(camera->x_axis), "toggled",
		G_CALLBACK(change_axis), &rt->info->axis.x);
	g_signal_connect(G_OBJECT(camera->display_width.spin), "value-changed",
		G_CALLBACK(display_width_scale_moved), rt);
	g_signal_connect(G_OBJECT(camera->display_height.spin), "value-changed",
		G_CALLBACK(display_height_scale_moved), rt);
	g_signal_connect(G_OBJECT(camera->fov.spin), "value-changed",
		G_CALLBACK(fov_scale_moved), rt);
	g_signal_connect(G_OBJECT(camera->fps.spin), "value-changed",
		G_CALLBACK(fps_scale_moved), rt);
	g_signal_connect(G_OBJECT(camera->pos[0].spin), "value-changed",
		G_CALLBACK(spin_button_camera_position_changer), rt);
	g_signal_connect(G_OBJECT(camera->pos[1].spin), "value-changed",
		G_CALLBACK(spin_button_camera_position_changer), rt);
	g_signal_connect(G_OBJECT(camera->pos[2].spin), "value-changed",
		G_CALLBACK(spin_button_camera_position_changer), rt);
}
