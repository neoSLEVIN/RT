/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_light_signals.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:27:55 by cschoen           #+#    #+#             */
/*   Updated: 2020/09/05 22:27:55 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_light_signals(t_rt *rt)
{
	t_gtk_light	*light;

	light = rt->gtk->ui.light;
	g_signal_connect(G_OBJECT(light->expander), "notify::expanded",
		G_CALLBACK(light_expander_callback), rt);
	g_signal_connect(G_OBJECT(light->name_changer),
		"key-press_event", G_CALLBACK(press_key_on_light_name), rt);
	g_signal_connect(G_OBJECT(light->type_combo),
		"changed", G_CALLBACK(changing_light_type), rt);
	g_signal_connect(G_OBJECT(light->intensity.spin), "value-changed",
		G_CALLBACK(spin_button_light_intensity_changer), rt);
	g_signal_connect(G_OBJECT(light->pos_x.spin), "value-changed",
		G_CALLBACK(spin_button_light_position_changer), rt);
	g_signal_connect(G_OBJECT(light->pos_y.spin), "value-changed",
		G_CALLBACK(spin_button_light_position_changer), rt);
	g_signal_connect(G_OBJECT(light->pos_z.spin), "value-changed",
		G_CALLBACK(spin_button_light_position_changer), rt);
	g_signal_connect(G_OBJECT(light->dir_x.spin), "value-changed",
		G_CALLBACK(spin_button_light_direction_changer), rt);
	g_signal_connect(G_OBJECT(light->dir_y.spin), "value-changed",
		G_CALLBACK(spin_button_light_direction_changer), rt);
	g_signal_connect(G_OBJECT(light->dir_z.spin), "value-changed",
		G_CALLBACK(spin_button_light_direction_changer), rt);
}
