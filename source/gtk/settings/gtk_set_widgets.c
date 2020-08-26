/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_widgets.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 15:30:54 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/29 06:11:50 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void		gtk_set_widgets(t_gtk *gtk, t_rt *rt)
{
	gtk->window_h_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_set_image_with_dependencies(gtk, rt->ocl->dto.buffer);
	gtk_set_ui_widgets(&gtk->ui);
	gtk_set_buttons_widgets(&gtk->ui.buttons);
	gtk_set_camera_widgets(&gtk->ui.camera, &rt->scene->cam);
	gtk_set_shape_widgets(&gtk->ui.shape, rt->scene);
	gtk_set_shapes_tree(&gtk->ui.shapes, rt);
	gtk_set_light_widgets(&gtk->ui.light, rt->scene);
	gtk_set_lights_tree(&gtk->ui.lights, rt);
	gtk_set_textures_tree(&gtk->ui.texture, "_Textures", rt->scene->textures);
	gtk_set_textures_tree(&gtk->ui.normals, "Normal _maps",
		rt->scene->normal_maps);
	gtk_set_settings_widgets(&gtk->ui.settings, rt);
}
