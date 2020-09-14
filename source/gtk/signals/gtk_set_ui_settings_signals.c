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
	g_signal_connect(G_OBJECT(settings->mirror.spin), "value-changed",
		G_CALLBACK(mirror_scale_moved), rt);
	g_signal_connect(G_OBJECT(settings->step.spin), "value-changed",
		G_CALLBACK(step_angle_scale_moved), rt);
	g_signal_connect(G_OBJECT(settings->angle.spin), "value-changed",
		G_CALLBACK(step_angle_scale_moved), rt);
	g_signal_connect(GTK_TOGGLE_BUTTON(settings->anti_aliasing), "toggled",
		G_CALLBACK(change_anti_aliasing), rt);
	g_signal_connect(G_OBJECT(settings->filter_combo), "changed",
		G_CALLBACK(changing_filter_type), rt);
	g_signal_connect(G_OBJECT(settings->blur.spin), "value-changed",
		G_CALLBACK(filter_spin_button_changer), rt);
	g_signal_connect(G_OBJECT(settings->sepia.spin), "value-changed",
		G_CALLBACK(filter_spin_button_changer), rt);
	g_signal_connect(G_OBJECT(settings->noise.spin), "value-changed",
		G_CALLBACK(filter_spin_button_changer), rt);
}
