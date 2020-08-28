/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/30 00:50:35 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_signals(t_rt *rt)
{
	gtk_set_buttons_signals(rt);
	gtk_set_motions_signals(rt->gtk->window, rt->gtk->img.image_event_box, rt);
	gtk_set_camera_signals(rt);
	gtk_set_shape_signals(rt);
	gtk_set_shapes_signals(rt);
	gtk_set_light_signals(rt);
	gtk_set_lights_signals(rt);
	gtk_set_textures_signals(rt);
	gtk_set_ui_settings_signals(&rt->gtk->ui.settings, rt);
	rt->gtk->timeout_id =
		g_timeout_add(1000 / rt->scene->cam.fps, draw_by_timeout, rt);
}
