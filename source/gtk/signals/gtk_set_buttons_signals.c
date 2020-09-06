/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_buttons_signals.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:27:49 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:27:49 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_buttons_signals(t_rt *rt)
{
	g_signal_connect(G_OBJECT(rt->gtk->ui.buttons.add_shape),
		"clicked", G_CALLBACK(new_shape), rt);
	g_signal_connect(G_OBJECT(rt->gtk->ui.buttons.add_light),
		"clicked", G_CALLBACK(new_light), rt);
	g_signal_connect(G_OBJECT(rt->gtk->ui.buttons.add_texture),
		"clicked", G_CALLBACK(new_texture), rt);
	g_signal_connect(G_OBJECT(rt->gtk->ui.buttons.add_normal_map),
		"clicked", G_CALLBACK(new_normal_map), rt);
	g_signal_connect(G_OBJECT(rt->gtk->ui.buttons.save_image),
		"clicked", G_CALLBACK(save_image), rt);
	g_signal_connect(G_OBJECT(rt->gtk->ui.buttons.save_image_as),
		"clicked", G_CALLBACK(save_image_as), rt);
	g_signal_connect(G_OBJECT(rt->gtk->ui.buttons.save_scene),
		"clicked", G_CALLBACK(save_scene), rt);
	g_signal_connect(G_OBJECT(rt->gtk->ui.buttons.save_scene_as),
		"clicked", G_CALLBACK(save_scene_as), rt);
}
