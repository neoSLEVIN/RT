/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_set_ui_settings_signals.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 06:42:37 by cschoen           #+#    #+#             */
/*   Updated: 2020/05/29 06:43:25 by cschoen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk_module.h"

void	gtk_set_ui_settings_signals(t_gtk_settings *settings, t_rt *rt)
{
	g_signal_connect(G_OBJECT(settings->fps_scale), "value-changed",
		G_CALLBACK(fps_scale_moved), rt);
	g_signal_connect(GTK_TOGGLE_BUTTON(settings->y_axis), "toggled",
		G_CALLBACK(change_axis), &rt->info->axis.y);
	g_signal_connect(GTK_TOGGLE_BUTTON(settings->x_axis), "toggled",
		G_CALLBACK(change_axis), &rt->info->axis.x);
	g_signal_connect(G_OBJECT(settings->filter_combo), "changed",
		G_CALLBACK(changing_filter_type), rt);
	g_signal_connect(G_OBJECT(settings->blur_size.spin), "value-changed",
		G_CALLBACK(spin_button_blur_filter_changer), rt);
	g_signal_connect(G_OBJECT(settings->sepia_depth.spin), "value-changed",
		G_CALLBACK(spin_button_sepia_filter_changer), rt);
	g_signal_connect(G_OBJECT(settings->noise_depth.spin), "value-changed",
		G_CALLBACK(spin_button_noise_filter_changer), rt);
	g_signal_connect(G_OBJECT(settings->fov.spin), "value-changed",
		G_CALLBACK(spin_button_fov_changer), rt);
}
